#include "game/input.hh"
#include "entt/entt.hpp"
#include "raylib.h"

void
yumeami::send_input_events(entt::dispatcher& dispatcher)
{
  // TODO: implement this
  if (IsKeyDown(KEY_DOWN)) {
    dispatcher.trigger(KeyboardKeyEvent{ KEY_DOWN });
  } else if (IsKeyDown(KEY_UP)) {
  }
}
