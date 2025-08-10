/**
 * @file world.hh
 * @brief World struct
 */

#pragma once
#include "entt/entt.hpp"
#include "game/texture.hh"
#include "raylib.h"
#include "util/units.hh"
#include <memory>

namespace yumeami {

  /**
   * @class World
   * @brief A dream world.
   *
   */
  struct World {
    tile_int width = 20;          // world width
    tile_int height = 15;         // world height
    spx_int tile_size = 16;       // size of tile
    int spx_multiplier = 2;       // sprite pixel multiplier
    entt::registry registry = {}; // entity registry
    Camera2D camera = {0};        // world camera

    // desired target. actual camera target might be
    // different if camera is at the border of a world.
    Vector2 desired_camera_target = {};

    // spritesheets
    std::vector<std::shared_ptr<Spritesheet>> spritesheets = {};
  };

  /**
   * @brief Calculate size of a tile in pixels.
   * @param world
   * @return tile size in px
   */
  int calc_px_tile_size(const World &world);

  /**
   * @brief Define camera target & origin
   * @param world World
   * @param viewport Viewport
   */
  void setup_camera(World &world, RenderTexture &viewport);

  /**
   * @brief Update camera
   * @param world World
   * @param viewport Viewport
   */
  void update_camera(World &world, RenderTexture &viewport);

} // namespace yumeami
namespace yumeami::impl {

  /**
   * @brief Update the camera's target as well as the desired target. Make the camera
   * target the player.
   * @param world
   */
  void update_camera_target(World &world);

  /**
   * @brief Check if camera gets out of bounds. If so, clamp the camera target.
   * @param world
   * @param viewport
   */
  void update_camera_bounds(World &world, RenderTexture &viewport);

} // namespace yumeami::impl
