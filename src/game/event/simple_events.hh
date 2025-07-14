#pragma once
#include "entt/entt.hpp"
#include "game/event/base.hh"
#include "util/simple_types.hh"

namespace yumeami::event {

  struct MoveEvent : Event
  {
    entt::entity target_entity;
    Direction4 direction;
  };

} // namespace yumeami::event
