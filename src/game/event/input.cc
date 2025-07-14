
#include "game/event/input.hh"
#include "entt/entt.hpp"
#include "game/event/simple_events.hh"
#include "game/event/simple_queues.hh"
#include "raylib.h"
#include "util/simple_types.hh"

void
yumeami::dispatch_input_events(entt::dispatcher& dispatcher)
{
  if (IsKeyDown(KEY_DOWN)) {
    dispatcher.trigger(event::MoveEvent{ .direction = Direction4::DOWN });

  } else if (IsKeyDown(KEY_UP)) {
    dispatcher.trigger(event::MoveEvent{ .direction = Direction4::UP });

  } else if (IsKeyDown(KEY_LEFT)) {
    dispatcher.trigger(event::MoveEvent{ .direction = Direction4::LEFT });

  } else if (IsKeyDown(KEY_RIGHT)) {
    dispatcher.trigger(event::MoveEvent{ .direction = Direction4::RIGHT });
  }
}

void
yumeami::sys::initialize_input_event_dispatcher(entt::dispatcher& dispatcher,
                                                entt::registry& registry)
{
  auto view = registry.view<comp::MoveEventQueue>();
  for (auto [entity, move_event_queue] : view.each()) {

    // connect keyboardkey events
    dispatcher.sink<event::MoveEvent>().connect<&comp::MoveEventQueue::receive>(
      move_event_queue);
  }
}
