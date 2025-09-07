#pragma once
#include "entt/entt.hpp"
#include "logic/world.hh"
namespace yumeami {

  /**
   * @brief Process gameplay inputs and send events accordingly
   * @param world
   * @param dispatcher dispatch events
   */
  void update_input(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
