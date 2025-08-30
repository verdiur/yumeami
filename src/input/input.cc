#include "input/input.hh"
#include "common/direction.hh"
#include "entt/entt.hpp"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "raylib.h"


void yumeami::update_input(World &world, entt::dispatcher &dispatcher) {
  // horrible implementation.
  // this is only temporary.
  auto view = world.reg.view<PlayerTag>();
  if (IsKeyDown(KEY_UP)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MovementEvent{
          .world = &world,
          .target = entity,
          .direction = Direction::UP,
      });
    }
  } else if (IsKeyDown(KEY_DOWN)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MovementEvent{
          .world = &world,
          .target = entity,
          .direction = Direction::DOWN,
      });
    }
  } else if (IsKeyDown(KEY_RIGHT)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MovementEvent{
          .world = &world,
          .target = entity,
          .direction = Direction::RIGHT,
      });
    }
  } else if (IsKeyDown(KEY_LEFT)) {
    for (auto [entity] : view.each()) {
      dispatcher.trigger(MovementEvent{
          .world = &world,
          .target = entity,
          .direction = Direction::LEFT,
      });
    }
  }
}
