#include "game/movement.hh"
#include "entt/entity/fwd.hpp"
#include "game/components.hh"

void yumeami::handle_move_event(MoveEvent &event) {
  World *world = event.world;
  entt::entity target = event.target;
  // does target exist?
  if (!world->registry.valid(target)) {
    return;
  }
  // does the target have the necessary components?
  if (!world->registry.all_of<TrueTilePos, DrawTilePos>(target)) {
    return;
  }
  // TODO: more checks and trigger movement...
}

void yumeami::setup_dispatcher_move(entt::dispatcher &dispatcher) {
  dispatcher.sink<MoveEvent>().connect<&handle_move_event>();
}
