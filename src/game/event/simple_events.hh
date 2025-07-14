#pragma once
#include "entt/entt.hpp"
#include "game/event/base.hh"
#include "util/simple_types.hh"

namespace yumeami::event {

  struct MoveEvent : public Event
  {
    Direction4 direction;
  };

} // namespace yumeami::event
