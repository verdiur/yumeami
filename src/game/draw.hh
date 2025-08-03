/**
 * @file draw.hh
 * @brief Draw functions
 */

#pragma once
#include "entt/fwd.hpp"
#include "game/world.hh"
#include "raylib.h"

namespace yumeami {

  /**
   * @brief Draw contents of registry.
   * @param world
   * @param viewport
   */
  void draw_registry(entt::registry &registry, RenderTexture &viewport);

  /**
   * @brief Draw world. Utility function that groups multiple draw functions for
   * convenience.
   *
   * @param world
   * @param viewport
   */
  void draw_world(World &world, RenderTexture &viewport);

} // namespace yumeami
