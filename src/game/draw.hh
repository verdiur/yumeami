/**
 * @file draw.hh
 * @brief Draw functions
 */

#pragma once
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "game/texture.hh"
#include "game/world.hh"
#include "raylib.h"

namespace yumeami {

  /**
   * @brief Draw contents of registry.
   * @param world
   * @param viewport
   */
  void draw_registry(World &world, RenderTexture &viewport);

  /**
   * @brief Draw world. Utility function that groups multiple draw functions for
   * convenience.
   *
   * @param world
   * @param viewport
   */
  void draw_world(World &world, RenderTexture &viewport);

} // namespace yumeami
namespace yumeami::impl {

  /**
   * @brief Draw solid color (used when tile isnt found)
   * @param draw_pos
   * @param world
   * @param tint
   */
  void draw_error_tile(const DrawTilePos &draw_pos, const World &world,
                       Color tint = MAGENTA);

  /**
   * @brief Draw sprite
   * TODO: add support for origin
   *
   * @param sprite
   * @param draw_pos
   * @param world
   */
  void draw_sprite(const Sprite &sprite, const DrawTilePos &draw_pos, const World &world);

} // namespace yumeami::impl
