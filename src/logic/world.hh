/**
 * @file world.hh
 * @brief World struct and functions
 */

#pragma once
#include "common/grid.hh"
#include "common/units.hh"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "raylib.h"
#include <random>
#include <vector>
namespace yumeami {

  /**
   * @class World
   * @brief World instance
   *
   */
  struct World {

    /**
     * @class Config
     * @brief World constants
     *
     */
    struct Config {
      tile width;
      tile height;
      spx tile_size;
      bool wrap;         // if true, world wrap is activated
      bool clamp_camera; // if true, the camera position will be limited to
                         // world bounds
      int scale = 2;
    } config;

    /**
     * @class Resources
     * @brief World resource-related fields
     *
     */
    struct Resources {
      std::vector<size_t> sheet_ids;
    } resources;

    /**
     * @class State
     * @brief World state-related fields, i.e. updated very frequently.
     * @warning collision and cam fields must be set up with setup_collision()
     * and setup_camera().
     *
     */
    struct State {
      entt::registry reg;
      Grid<int> collision;
      Camera2D cam;
      std::mt19937 rd = {};
    } state;
  };

  using WorldConfig = World::Config;
  using WorldResources = World::Resources;
  using WorldState = World::State;

  World create_world(const World::Config &config,
                     const World::Resources &resources);

  /**
   * @brief Sets up collision grid of a world. Does not check if the grid is
   * blank. For each entity with a collision tag, it increments the
   * corresponding position on the grid.
   *
   * @return
   */
  void setup_world_collision(World &world);

} // namespace yumeami
