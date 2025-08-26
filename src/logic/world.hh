/**
 * @file world.hh
 * @brief World struct and functions
 */

#pragma once
#include "common/units.hh"
#include <entt/entt.hpp>
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
    int scale;
    bool wrap;

    entt::registry reg;
    std::vector<std::string> sheet_ids;
  };

} // namespace yumeami
