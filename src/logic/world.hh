/**
 * @file world.hh
 * @brief World struct and functions
 */

#pragma once
#include "common/grid.hh"
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
    Grid<int> collision;
    Camera2D cam{};
  };

  World create_world(tile width, tile height, spx tile_size, bool wrap,
                     bool clamp_camera, std::vector<std::string> sheet_ids = {},
                     int scale = 2);

  /**
   * @brief Sets up collision grid of a world. Does not check if the grid is
   * blank. For each entity with a collision tag, it increments the
   * corresponding position on the grid.
   *
   * @return
   */
  void setup_world_collision(World &world);

  /**
   * @brief Clear the entirety of a world's entity registry.
   * @param world
   */
  void unload_world_registry(World &world);

} // namespace yumeami
