#include "logic/movement.hh"
#include "ai/base.hh"
#include "logic/collision.hh"
#include "logic/components.hh"
#include "logic/components_op.hh"
#include "logic/event_op.hh"
#include "spdlog/spdlog.h"
#include <optional>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  /**
   * @class MovementComponents
   * @brief Simple container for all components used for movement
   *
   */
  struct MovementComponents {
    TruePos *true_pos;
    DrawPos *draw_pos;
    MovementState *movement_state;
    Facing *facing;
    Velocity *velocity;
    bool has_collision;
  };


  /**
   * @class MovementCoords
   * @brief A pair of movement source and destination coordinates.
   *
   */
  struct MovementCoords {
    TruePos src;
    TruePos dst;
  };


  bool tgt_exists(const MovementEvent &event) {
    bool val = event.world->state.reg.valid(event.target);
    if (!val) {
      spdlog::warn("[MovementEvent] target not found");
      return false;
    }
    return true;
  }


  std::optional<MovementComponents> get_components(const MovementEvent &event) {
    WorldState &wstate = event.world->state;
    entt::entity target = event.target;

    auto true_pos = wstate.reg.try_get<TruePos>(target);
    auto draw_pos = wstate.reg.try_get<DrawPos>(target);
    auto mvt_state = wstate.reg.try_get<MovementState>(target);
    auto facing = wstate.reg.try_get<Facing>(target);
    auto velocity = wstate.reg.try_get<Velocity>(target);
    bool has_coll = wstate.reg.view<CollisionTag>().contains(target);

    if (!true_pos || !draw_pos || !mvt_state || !velocity) {
      spdlog::warn("[MovementEvent] target does not have required components");
      return std::nullopt;
    }

    return MovementComponents{
        .true_pos = true_pos,
        .draw_pos = draw_pos,
        .movement_state = mvt_state,
        .facing = facing,
        .velocity = velocity,
        .has_collision = has_coll,
    };
  }


  bool is_moving(const MovementComponents &components) {
    return components.movement_state->moving;
  }


  void try_update_facing(const MovementEvent &event,
                         MovementComponents &components) {
    if (components.facing)
      components.facing->dir = event.direction;
  }


  bool dst_collides(const MovementEvent &event, const MovementCoords &coords) {
    int collision_value =
        event.world->state.collision.at(coords.dst.x, coords.dst.y);
    return collision_value > 0;
  }


  /**
   * @brief Calculates movement source and destination. Destination might be out
   * of bounds.
   *
   * @param event
   * @param components
   * @return movement coordinates
   */
  MovementCoords calc_raw_coords(const MovementEvent &event,
                                 const MovementComponents &components) {
    return MovementCoords{
        .src = *components.true_pos,
        .dst = direction_to_true_pos(*components.true_pos, event.direction),
    };
  }


  bool dst_is_oob(const MovementEvent &event,
                  const MovementComponents &components) {
    const WorldConfig &wconfig = event.world->config;
    const MovementState &mvst = *components.movement_state;
    if (mvst.dst.x < 0 || mvst.dst.y < 0)
      return true;
    if (mvst.dst.x >= wconfig.width || mvst.dst.y >= wconfig.height)
      return true;
    return false;
  }


  /**
   * @brief Calculates wrapped destination and ADJUSTED SOURCE. The source
   * position will always be 1 tile behind the destination, so it might end up
   * out of bounds. To access the actual modulo'd coordinates:
   * - src should be from the raw coords;
   * - dst should be from the wrapped coords.
   *
   * @param event
   * @param raw
   * @return "wrapped" movement coordinates
   */
  MovementCoords calc_wrapped_dst_and_adjust_src(const MovementEvent &event,
                                                 const MovementCoords &raw) {
    // NOTE: implementation is a little flimsy
    const WorldConfig &wconfig = event.world->config;
    MovementCoords wrapped = raw;

    if (raw.dst.x < 0) {
      wrapped.dst.x += wconfig.width;
      wrapped.src.x = wrapped.dst.x + 1;
    }
    if (raw.dst.x >= wconfig.width) {
      wrapped.dst.x -= wconfig.width;
      wrapped.src.x = wrapped.dst.x - 1;
    }
    if (raw.dst.y < 0) {
      wrapped.dst.y += wconfig.height;
      wrapped.src.y = wrapped.dst.y + 1;
    }
    if (raw.dst.y >= wconfig.height) {
      wrapped.dst.y -= wconfig.height;
      wrapped.src.y = wrapped.dst.y - 1;
    }

    return wrapped;
  }


  /**
   * @brief Apply some movement coordinates to the movement state component.
   * @param coord
   * @param components
   */
  void set_coords(MovementCoords &coord, MovementComponents &components) {
    components.movement_state->src = coord.src;
    components.movement_state->dst = coord.dst;

    // set new true_pos before animation begins
    *components.true_pos = coord.dst;
  }


  void begin_movement(MovementComponents &components) {
    components.movement_state->moving = true;
    components.movement_state->progress = 0;
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<MovementEvent>().connect<&handle_movement_event>();
}


void yumeami::handle_movement_event(const MovementEvent &event) {
  if (!check_world_pointer(event.world) ||
      !check_dispatcher_pointer(event.dispatcher))
    return;

  if (!tgt_exists(event))
    return;

  std::optional<MovementComponents> components_opt = get_components(event);
  if (!components_opt)
    return;

  MovementComponents components = components_opt.value();

  if (is_moving(components))
    return;

  try_update_facing(event, components);

  MovementCoords raw_coords = calc_raw_coords(event, components);
  MovementCoords wrapped_coords =
      calc_wrapped_dst_and_adjust_src(event, raw_coords);

  if (dst_collides(event, wrapped_coords))
    return;

  if (dst_is_oob(event, components) && !event.world->config.wrap)
    return;

  // collision updates must be triggered on the spot
  if (components.has_collision) {
    event.dispatcher->trigger(UpdateCollisionEvent{
        .world = event.world,
        .src = raw_coords.src,
        .dst = wrapped_coords.dst,
    });
  }

  set_coords(wrapped_coords, components);
  begin_movement(components);
}


void yumeami::update_movement_state(World &world,
                                    entt::dispatcher &dispatcher) {
  WorldState &wstate = world.state;
  auto view = wstate.reg.view<TruePos, DrawPos, MovementState, Velocity>();
  for (auto [ent, true_pos, draw_pos, mvt_state, velocity] : view.each()) {
    if (!mvt_state.moving)
      continue;

    mvt_state.progress += (1 / velocity) * GetFrameTime();
    draw_pos = {
        .x = std::lerp(mvt_state.src.x, mvt_state.dst.x, mvt_state.progress),
        .y = std::lerp(mvt_state.src.y, mvt_state.dst.y, mvt_state.progress),
    };

    // when movement is finished
    if (mvt_state.progress >= 1) {
      mvt_state.moving = false;
      mvt_state.progress = 0;
      draw_pos = to_draw_pos(true_pos); // snap draw_pos

      if (!wstate.reg.view<PlayerTag>().contains(ent))
        dispatcher.trigger(ActionFinishedEvent{
            .world = &world,
            .target = ent,
        });
    }
  }
}
