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
#include <string>
#include <vector>
namespace yumeami {

  /**
   * @class World
   * @brief An instance of a world (old)
   *
   */
  struct WorldOld {
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
      std::vector<std::string> sheet_ids;
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
    } state;
  };

  using WorldConfig = World::Config;
  using WorldResources = World::Resources;
  using WorldState = World::State;

  // World create_world(tile width, tile height, spx tile_size, bool wrap,
  //                    bool clamp_camera, std::vector<std::string> sheet_ids =
  //                    {}, int scale = 2);


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

  /**
   * @brief Clear the entirety of a world's entity registry.
   * @param world
   */
  void unload_world_registry(World &world);

} // namespace yumeami
