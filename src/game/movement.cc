#include "game/movement.hh"
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "spdlog/spdlog.h"

void yumeami::handle_move_event(const MoveEvent &event) {
  World *world = event.world;
  entt::entity target = event.target;

  // does the target exist?
  if (!world->registry.valid(target)) {
    spdlog::warn("handle_move_event: target does not exist. This event will be ignored.");
    return;
  }

  // does the target have the necessary components?
  if (!world->registry.all_of<TrueTilePos, DrawTilePos, Movement>(target)) {
    spdlog::warn("handle_move_event: target does not have necessary components. This "
                 "event will be ignored.");
    return;
  }

  // extract components
  auto &true_tile_pos = world->registry.get<TrueTilePos>(target);
  auto &draw_tile_pos = world->registry.get<DrawTilePos>(target);
  auto &movement = world->registry.get<Movement>(target);

  // is the target already in movement?
  if (movement.is_moving) {
    return;
  }

  // TODO: check collision, wrap, OOB
  // TODO: trigger movement
}

void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<MoveEvent>().connect<&handle_move_event>();
}

void yumeami::update_movement(World &world) {
  // TODO:
}
