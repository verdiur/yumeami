#include "game/event/input.hh"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "game/event/simple_events.hh"
#include "game/simple_components.hh"
#include "raylib.h"
#include "util/simple_types.hh"

void
yumeami::sys::dispatch_input_events(entt::registry& registry,
                                    entt::dispatcher& dispatcher)
{
  auto view = registry.view<comp::ControllableFlag>();
  for (auto [entity] : view.each()) {
    if (IsKeyDown(KEY_DOWN)) {
      dispatcher.trigger(event::MoveEvent{ entity, Direction4::DOWN });

    } else if (IsKeyDown(KEY_UP)) {
      dispatcher.trigger(event::MoveEvent{ entity, Direction4::UP });

    } else if (IsKeyDown(KEY_LEFT)) {
      dispatcher.trigger(event::MoveEvent{ entity, Direction4::LEFT });

    } else if (IsKeyDown(KEY_RIGHT)) {
      dispatcher.trigger(event::MoveEvent{ entity, Direction4::RIGHT });
    }
  }
}
