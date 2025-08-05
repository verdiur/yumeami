#include "game/input.hh"
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "game/movement.hh"
#include "raylib.h"
#include "util/direction.hh"

void yumeami::input(World &world, entt::dispatcher &dispatcher) {
  auto view = world.registry.view<PlayerTag, Velocity>();
  if (IsKeyDown(KEY_LEFT)) {
    for (auto [entity, velocity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::LEFT});
    }
  } else if (IsKeyDown(KEY_RIGHT)) {
    for (auto [entity, velocity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::RIGHT});
    }
  } else if (IsKeyDown(KEY_UP)) {
    for (auto [entity, velocity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::TOP});
    }
  } else if (IsKeyDown(KEY_DOWN)) {
    for (auto [entity, velocity] : view.each()) {
      dispatcher.trigger(MoveEvent{entity, &world, Direction4::BOTTOM});
    }
  }

  if (IsKeyPressed(KEY_LEFT_SHIFT)) {
    for (auto [entity, velocity] : view.each()) {
      velocity.vel = velocity.vel / 2;
    }
  } else if (IsKeyReleased(KEY_LEFT_SHIFT)) {
    for (auto [entity, velocity] : view.each()) {
      velocity.vel = velocity.vel * 2;
    }
  }
}
