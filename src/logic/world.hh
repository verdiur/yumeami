/**
 * @file world.hh
 * @brief World struct and functions
 */

#pragma once
#include "common/units.hh"
#include "entt/entt.hpp"
#include "raylib.h"
#include <string>
#include <vector>
namespace yumeami {

  /**
   * @class World
   * @brief An instance of a world
   *
   */
  struct World {
    tile width;
    tile height;
    spx tile_size;
    bool wrap;         // if true, world wrap is activated
    bool clamp_camera; // if true, the camera position will be limited to world
                       // bounds (i.e. the player will never be able to see
                       // beyond the borders)
    int scale = 2;

    std::vector<std::string> sheet_ids;
    entt::registry reg = {};
    Camera2D cam{};
  };

  /**
   * @brief Clear the entirety of a world's entity registry.
   * @param world
   */
  void unload_world_registry(World &world);

} // namespace yumeami
