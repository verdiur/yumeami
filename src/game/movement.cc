#include "game/movement.hh"
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "spdlog/spdlog.h"

void yumeami::handle_move_event(const MoveEvent &event) {
  World *world = event.world;
  entt::entity target = event.target;

  // does the target exist?
  if (!world->registry.valid(target)) {
    spdlog::warn("handle_move_event: target does not exist");
    return;
  }

  // does the target have the necessary components?
  if (!world->registry.all_of<TrueTilePos, DrawTilePos>(target)) {
    spdlog::warn("handle_move_event: target does not have necessary components");
    return;
  }

  // TODO: more checks and trigger movement...
}

void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<MoveEvent>().connect<&handle_move_event>();
}
