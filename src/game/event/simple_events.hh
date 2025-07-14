#pragma once
#include "game/event/base.hh"
#include "util/simple_types.hh"

namespace yumeami::event {

  struct MoveEvent : Event
  {
    Direction4 direction;
  };

} // namespace yumeami::event
