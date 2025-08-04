#include "game/movement.hh"
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "game/conversions.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <cmath>


void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<MoveEvent>().connect<&handle_move_event>();
}


void yumeami::handle_move_event(const MoveEvent &event) {
  entt::registry &registry = event.world->registry;
  const entt::entity target = event.target;

  if (!registry.valid(target)) {
    spdlog::warn("handle_move_event: target does not exist. This event will be ignored.");
    return;
  }

  if (!registry.all_of<TrueTilePos, DrawTilePos, Velocity, Movement>(target)) {
    spdlog::warn("handle_move_event: target does not have necessary components. This "
                 "event will be ignored.");
    return;
  }

  auto &true_tile_pos = registry.get<TrueTilePos>(target);
  auto &draw_tile_pos = registry.get<DrawTilePos>(target);
  auto &movement = registry.get<Movement>(target);

  if (movement.is_moving) {
    return;
  }

  // if entity has facing, update it
  if (registry.all_of<Facing>(target)) {
    auto &facing = registry.get<Facing>(target);
    facing.fac = event.direction;
  }

  movement.from = true_tile_pos;
  movement.to = calc_true_tile_pos_from_direction4(true_tile_pos, event.direction);
  true_tile_pos = movement.to;
  movement.progress = 0;
  movement.is_moving = true;
}


void yumeami::update_movement(World &world) {
  auto view = world.registry.view<TrueTilePos, DrawTilePos, Velocity, Movement>();
  for (auto [entity, true_pos, draw_pos, velocity, movement] : view.each()) {

    if (movement.is_moving) {
      movement.progress += (1 / velocity.vel) * GetFrameTime();
      draw_pos.x = std::lerp(movement.from.x, movement.to.x, movement.progress);
      draw_pos.y = std::lerp(movement.from.y, movement.to.y, movement.progress);

      if (movement.progress >= 1) {
        draw_pos = to_draw_tile_pos(movement.to);
        movement.progress = 0;
        movement.is_moving = false;
      }
    }
  }
}
