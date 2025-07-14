#pragma once

#include "game/event/base.hh"
#include "game/event/simple_events.hh"

namespace yumeami::comp {

  struct MoveEventQueue : EventQueue<event::MoveEvent>
  {};

} // namespace yumeami::comp
