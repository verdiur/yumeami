#pragma once
#include "entt/entt.hpp"
#include "game/event/base.hh"
#include "util/simple_types.hh"

namespace yumeami::event {

  /**
   * @class MoveEvent
   * @brief Signals that the targeted entity should move.
   *
   */
  struct MoveEvent : public Event
  {
    Direction4 direction;
  };

} // namespace yumeami::event
