/**
 * @file draw.hh
 * @brief Draw functions
 */

#pragma once
#include "entt/fwd.hpp"
#include "game/world.hh"

namespace yumeami {

  /**
   * @brief Render world
   *
   * @param reg Entity registry
   */
  void draw_world(World &world);

} // namespace yumeami
