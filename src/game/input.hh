#pragma once
#include "entt/entt.hpp"
#include "raylib.h"

namespace yumeami {

  /**
   * @class KeyboardKeyEvent
   * @brief Event to dispatch when a key is pressed
   *
   */
  struct KeyboardKeyEvent
  {
    KeyboardKey key;
  };

  void send_input_events(entt::dispatcher& dispatcher);

} // namespace yumeami
