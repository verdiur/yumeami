#include "game/input.hh"
#include "entt/signal/fwd.hpp"
#include "game/components.hh"
#include "game/movement.hh"
#include "raylib.h"
#include "util/direction.hh"

void yumeami::input(World &world, entt::dispatcher &dispatcher) {
  auto view = world.registry.view<PlayerFlag>();
  if (IsKeyDown(KEY_LEFT)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::LEFT});
    }
  } else if (IsKeyDown(KEY_RIGHT)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::RIGHT});
    }
  } else if (IsKeyDown(KEY_UP)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::TOP});
    }
  } else if (IsKeyDown(KEY_DOWN)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::BOTTOM});
    }
  }
}
