/**
 * @file world.hh
 * @brief World struct and functions
 */

#pragma once
#include "common/units.hh"
#include "entt/entt.hpp"
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
    bool wrap;
    int scale;

    entt::registry reg;
    std::vector<std::string> sheet_ids;
  };

} // namespace yumeami
