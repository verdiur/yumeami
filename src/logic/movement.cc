#include "logic/movement.hh"
#include "entt/entt.hpp"
#include "logic/collision.hh"
#include "logic/components.hh"
#include "logic/components_op.hh"
#include "spdlog/spdlog.h"
#include <optional>


/* IMPL ***********************************************************************/


bool yumeami::impl::movement_tgt_exists(const MovementEvent &event) {
  bool val = event.world->reg.valid(event.target);
  if (!val) {
    spdlog::warn("[MovementEvent] target not found");
    return false;
  }
  return true;
}


std::optional<yumeami::impl::MovementComponents>
yumeami::impl::movement_get_components(const MovementEvent &event) {
  World &world = *event.world;
  entt::entity target = event.target;

  auto true_pos = world.reg.try_get<TruePos>(target);
  auto draw_pos = world.reg.try_get<DrawPos>(target);
  auto mvt_state = world.reg.try_get<MovementState>(target);
  auto facing = world.reg.try_get<Facing>(target);
  auto velocity = world.reg.try_get<Velocity>(target);
  bool has_coll = world.reg.view<CollisionTag>().contains(target);

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


bool yumeami::impl::movement_is_moving(const MovementComponents &components) {
  return components.movement_state->moving;
}


void yumeami::impl::movement_try_update_facing(const MovementEvent &event,
                                               MovementComponents &components) {
  if (components.facing)
    components.facing->dir = event.direction;
}


bool yumeami::impl::movement_collides(const MovementEvent &event,
                                      const MovementCoords &coords) {
  int collision_value = event.world->collision.at(coords.dst.x, coords.dst.y);
  return collision_value > 0;
}


yumeami::impl::MovementCoords
yumeami::impl::movement_calc_raw_coords(const MovementEvent &event,
                                        const MovementComponents &components) {
  return MovementCoords{
      .src = *components.true_pos,
      .dst = direction_to_true_pos(*components.true_pos, event.direction),
  };
}


bool yumeami::impl::movement_is_oob(const MovementEvent &event,
                                    const MovementComponents &components) {
  const MovementState &mvst = *components.movement_state;
  if (mvst.dst.x < 0 || mvst.dst.y < 0)
    return true;
  if (mvst.dst.x >= event.world->width || mvst.dst.y >= event.world->height)
    return true;
  return false;
}


yumeami::impl::MovementCoords
yumeami::impl::movement_calc_wrapped_dst_and_adjust_src(
    const MovementEvent &event, const MovementCoords &raw) {
  // NOTE: implementation is a little flimsy
  MovementCoords wrapped = raw;
  const World &world = *event.world;

  if (raw.dst.x < 0) {
    wrapped.dst.x += world.width;
    wrapped.src.x = wrapped.dst.x + 1;
  }
  if (raw.dst.x >= world.width) {
    wrapped.dst.x -= world.width;
    wrapped.src.x = wrapped.dst.x - 1;
  }
  if (raw.dst.y < 0) {
    wrapped.dst.y += world.height;
    wrapped.src.y = wrapped.dst.y + 1;
  }
  if (raw.dst.y >= world.height) {
    wrapped.dst.y -= world.height;
    wrapped.src.y = wrapped.dst.y - 1;
  }

  return wrapped;
}


void yumeami::impl::movement_set_coords(MovementCoords &coord,
                                        MovementComponents &components) {
  components.movement_state->src = coord.src;
  components.movement_state->dst = coord.dst;

  // set new true_pos before animation begins
  *components.true_pos = coord.dst;
}


void yumeami::impl::movement_begin(MovementComponents &components) {
  components.movement_state->moving = true;
  components.movement_state->progress = 0;
}


/* PUBL ***********************************************************************/


void yumeami::setup_movement_event_dispatcher(entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
    .sink<MovementEvent>()
    .connect<&handle_movement_event>();
  // clang-format on
}


void yumeami::handle_movement_event(const MovementEvent &event) {
  if (!impl::movement_tgt_exists(event))
    return;

  std::optional<impl::MovementComponents> components_opt =
      impl::movement_get_components(event);
  if (!components_opt)
    return;

  impl::MovementComponents components = components_opt.value();

  // spdlog::info("handling movement");
  if (impl::movement_is_moving(components))
    return;

  impl::movement_try_update_facing(event, components);

  // clang-format off
  impl::MovementCoords raw_coords = impl::movement_calc_raw_coords(event, components);
  impl::MovementCoords wrapped_coords = impl::movement_calc_wrapped_dst_and_adjust_src(event, raw_coords);
  // clang-format on

  if (impl::movement_collides(event, wrapped_coords))
    return;

  if (impl::movement_is_oob(event, components) && !event.world->wrap)
    return;

  if (components.has_collision) {
    event.dispatcher->trigger(UpdateCollisionEvent{
        .world = event.world,
        .src = raw_coords.src,
        .dst = wrapped_coords.dst,
    });
  }

  impl::movement_set_coords(wrapped_coords, components);
  impl::movement_begin(components);
}


void yumeami::update_movement_state(World &world) {
  auto view = world.reg.view<TruePos, DrawPos, MovementState, Velocity>();
  for (auto [ent, true_pos, draw_pos, mvt_state, velocity] : view.each()) {

    if (mvt_state.moving) {
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
      }
    }
  }
}
