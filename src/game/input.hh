/**
 * @file input.hh
 * @brief Input-related functions
 */

#pragma once
#include "entt/signal/fwd.hpp"
#include "game/world.hh"

namespace yumeami {

  /**
   * @brief Handle input
   * @param world
   * @param dispatcher
   */
  void input(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
