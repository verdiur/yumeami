
#include "game/event/input.hh"
#include "entt/entt.hpp"
#include "raylib.h"
#include <cassert>
#include <queue>

void
yumeami::dispatch_input_events(entt::dispatcher& dispatcher)
{
  if (IsKeyDown(KEY_DOWN)) {
    dispatcher.trigger(KeyboardKeyEvent{ .key = KEY_DOWN });

  } else if (IsKeyDown(KEY_UP)) {
    dispatcher.trigger(KeyboardKeyEvent{ .key = KEY_UP });

  } else if (IsKeyDown(KEY_LEFT)) {
    dispatcher.trigger(KeyboardKeyEvent{ .key = KEY_LEFT });

  } else if (IsKeyDown(KEY_RIGHT)) {
    dispatcher.trigger(KeyboardKeyEvent{ .key = KEY_RIGHT });
  }
}

/* BEGIN KeyboardKeyQueue IMPLEMENTATION ************************************************/

const std::queue<KeyboardKey>&
yumeami::comp::KeyboardKeyQueue::get_queue() const
{
  return queue;
}

void
yumeami::comp::KeyboardKeyQueue::receive(const KeyboardKeyEvent& event)
{
  queue.push(event.key);
}

KeyboardKey
yumeami::comp::KeyboardKeyQueue::consume()
{
  if (queue.empty()) {
    return KEY_NULL;
  }
  KeyboardKey key = queue.front();
  queue.pop();
  return key;
}

void
yumeami::comp::KeyboardKeyQueue::clear()
{
  std::queue<KeyboardKey>().swap(queue);
}

/* END KeyboardKeyQueue IMPLEMENTATION **************************************************/

void
yumeami::sys::initialize_input_event_dispatcher(entt::dispatcher& dispatcher,
                                                entt::registry& registry)
{
  auto view = registry.view<comp::KeyboardKeyQueue>();
  for (auto [entity, keyboard_key_queue] : view.each()) {

    // connect keyboardkey events
    dispatcher.sink<KeyboardKeyEvent>().connect<&comp::KeyboardKeyQueue::receive>(
      keyboard_key_queue);
  }
}
