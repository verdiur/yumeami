#include "logic/movement/movement.hh"
#include "common/types/direction.hh"
#include "common/types/vector.hh"
#include "common/variant_helpers.hh"
#include "logic/utils/event.hh"
#include "model/components/components.hh"
#include "model/components/movement.hh"
#include "model/world/world.hh"
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <utility>
#include <variant>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  struct MovementComponents {
    TrueTilePos *true_pos;
    DrawTilePos *draw_pos;
    MovementData *data;
    Facing *facing;
    Velocity *velocity;
    bool collision_tag;
    bool player_tag;
  };


  struct MovementCoords {
    TrueTilePos src;
    TrueTilePos dst;
  };


  std::optional<MovementComponents>
  get_components(const EntityMoveCommand &cmd) {
    WorldState &wstate = cmd.world->state;
    entt::entity target = cmd.target;

    auto true_pos = wstate.registry.try_get<TrueTilePos>(target);
    auto draw_pos = wstate.registry.try_get<DrawTilePos>(target);
    auto data = wstate.registry.try_get<MovementData>(target);
    auto facing = wstate.registry.try_get<Facing>(target);
    auto velocity = wstate.registry.try_get<Velocity>(target);
    bool collision_tag = wstate.registry.view<CollisionTag>().contains(target);
    bool player_tag = wstate.registry.view<PlayerTag>().contains(target);

    if (!true_pos || !draw_pos || !data || !velocity) {
      return std::nullopt;
    }

    return MovementComponents{
        .true_pos = true_pos,
        .draw_pos = draw_pos,
        .data = data,
        .facing = facing,
        .velocity = velocity,
        .collision_tag = collision_tag,
        .player_tag = player_tag,
    };
  }


  bool is_moving(const MovementComponents &components) {
    auto state = components.data->state;
    return std::holds_alternative<MovementStateMoving>(state);
  }


  void try_update_facing(const EntityMoveCommand &cmd,
                         MovementComponents &components) {
    if (components.facing) {
      components.facing->dir = cmd.direction;
    }
  }


  MovementCoords calc_raw_coords(const EntityMoveCommand &cmd,
                                 const MovementComponents &components) {
    Vector2 dst_vec = direction_to_vector(cmd.direction);
    TrueTilePos src = *components.true_pos;
    TrueTilePos dst = {{
        (float)src.pos.x + (float)dst_vec.x,
        (float)src.pos.y + (float)dst_vec.y,
    }};
    return MovementCoords{src, dst};
  }


  std::pair<MovementCoords, bool>
  calc_wrapped_coords(const EntityMoveCommand &cmd, const MovementCoords &raw) {
    const WorldConfig &wconfig = cmd.world->config;
    MovementCoords wrapped = raw;
    bool wrap_status = false;

    if ((float)raw.dst.pos.x < 0) {
      wrapped.dst.pos.x += wconfig.width;
      wrapped.src.pos.x = (float)wrapped.dst.pos.x + 1;
      wrap_status = true;
    }
    if ((float)raw.dst.pos.x >= (float)wconfig.width) {
      wrapped.dst.pos.x -= wconfig.width;
      wrapped.src.pos.x = (float)wrapped.dst.pos.x - 1;
      wrap_status = true;
    }
    if ((float)raw.dst.pos.y < 0) {
      wrapped.dst.pos.y += wconfig.height;
      wrapped.src.pos.y = (float)wrapped.dst.pos.y + 1;
      wrap_status = true;
    }
    if ((float)raw.dst.pos.y >= (float)wconfig.height) {
      wrapped.dst.pos.y -= wconfig.height;
      wrapped.src.pos.y = (float)wrapped.dst.pos.y - 1;
      wrap_status = true;
    }

    return std::make_pair(wrapped, wrap_status);
  }


  bool dst_collides(const EntityMoveCommand &cmd,
                    const MovementCoords &coords) {
    int collision_value =
        cmd.world->state.collision.at(coords.dst.pos.x, coords.dst.pos.y);
    return collision_value > 0;
  }


  bool dst_is_oob(const EntityMoveCommand &cmd, const MovementCoords &raw) {
    const WorldConfig &wconfig = cmd.world->config;
    if (std::trunc((float)raw.dst.pos.x) < 0 ||
        std::trunc((float)raw.dst.pos.y) < 0) {
      return true;
    }
    if (std::trunc((float)raw.dst.pos.x) < std::trunc((float)wconfig.width) ||
        std::trunc((float)raw.dst.pos.y) < std::trunc((float)wconfig.height)) {
      return true;
    }
    return false;
  }


  void set_coords(const MovementCoords &coords,
                  MovementComponents &components) {
    components.data->src = coords.src;
    components.data->dst = coords.dst;
    // set new TrueTilePos
    *components.true_pos = coords.dst;
  }


  void begin_movement(MovementComponents &components) {
    components.data->state = MovementStateMoving{.progress = 0};
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<EntityMoveCommand>().connect<&handle_entity_move_command>();
}


void yumeami::handle_entity_move_command(const EntityMoveCommand &cmd) {
  if (!is_event_valid(cmd)) {
    return;
  }
  if (!event_entity_exists(cmd.world, cmd.target, "EntityMoveCommand")) {
    return;
  }
  std::optional<MovementComponents> components_opt = get_components(cmd);
  if (!components_opt) {
    return;
  }
  MovementComponents &components = components_opt.value();
  if (is_moving(components)) {
    return;
  }
  try_update_facing(cmd, components);
  MovementCoords raw_coords = calc_raw_coords(cmd, components);
  auto [wrapped_coords, wrap_status] = calc_wrapped_coords(cmd, raw_coords);
  if (dst_collides(cmd, wrapped_coords)) {
    return;
  }
  if (dst_is_oob(cmd, raw_coords) && !cmd.world->config.wrap) {
    return;
  }
  set_coords(wrapped_coords, components);
  begin_movement(components);
  cmd.dispatcher->trigger(EntityMoveStartEvent{
      cmd.world,
      cmd.dispatcher,
      cmd.target,
  });
}


void yumeami::update_movement_state(World &world,
                                    entt::dispatcher &dispatcher) {
  WorldState &wstate = world.state;
  auto view =
      wstate.registry.view<TrueTilePos, DrawTilePos, MovementData, Velocity>();
  for (auto [ent, true_pos, draw_pos, mvt_data, velocity] : view.each()) {
    auto visitor = Match{

        [](MovementStateIdle &) {},

        [&](MovementStateMoving &moving) {
          moving.progress += GetFrameTime() / velocity.vel;

          TileVector2 mvt_src = mvt_data.src.pos;
          TileVector2 mvt_dst = mvt_data.dst.pos;
          draw_pos.pos = {
              .x = std::lerp(mvt_src.x, mvt_dst.x, moving.progress),
              .y = std::lerp(mvt_src.y, mvt_dst.y, moving.progress),
          };

          if (moving.progress >= 1) {
            draw_pos.pos = true_pos.pos;
            dispatcher.trigger(EntityMoveFinishEvent{
                &world,
                &dispatcher,
                ent,
            });
            mvt_data.state = MovementStateIdle{};
          }
        },

    };
    std::visit(visitor, mvt_data.state);
  }
}
