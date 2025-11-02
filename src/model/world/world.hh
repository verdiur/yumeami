#pragma once
#include "common/grid/grid.hh"
#include "common/units/tile.hh"
#include "common/units/tx.hh"
#include <entt/entity/registry.hpp>
#include <random>
#include <raylib.h>
namespace yumeami {

  /**
   * @class WorldConfig
   * @brief World configuration
   *
   */
  struct WorldConfig {
    tile width;
    tile height;
    tx tile_size;
    bool wrap;
    bool clamp_camera;
  };

  /**
   * @class WorldResource
   * @brief World resource handles
   *
   */
  struct WorldResources {
    int dummy;
  };

  /**
   * @class WorldState
   * @brief World state
   *
   */
  struct WorldState {
    entt::registry registry;
    Grid<int> collision;
    Camera2D camera;
  };

  /**
   * @class WorldTools
   * @brief World tools (utility classes)
   *
   */
  struct WorldTools {
    std::mt19937 rd;
  };

  /**
   * @class World
   * @brief World instance
   *
   */
  struct World {
    WorldConfig config;
    WorldResources resources;
    WorldState state;
    WorldTools tools;
  };

} // namespace yumeami
