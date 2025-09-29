#pragma once
#include "logic/movement.hh"
#include "logic/world.hh"
#include "spdlog/spdlog.h"
namespace yumeami {


  inline bool check_world_pointer(World *world) {
    if (!world)
      spdlog::error("[Event] world pointer is null");
    return world;
  }


  inline bool check_dispatcher_pointer(entt::dispatcher *dispatcher) {
    if (!dispatcher)
      spdlog::error("[Event] dispatcher pointer is null");
    return dispatcher;
  }

} // namespace yumeami
