/**
 * @file world_io.hh
 * @brief World I/O
 */

#pragma once

#include "game/world.hh"
#include "rfl/Description.hpp"
#include <filesystem>
#include <string>

namespace yumeami {

  /**
   * @class SpritesheetSpec
   * @brief Spritesheet JSON specification
   *
   */
  struct SpritesheetSpec {
    // clang-format off
    rfl::Description<"Path to texture file. Must be relative to the parent folder of "
      "world.json", std::string>
      path;
    rfl::Description<"Width of a sprite", int>
      sprite_width;
    rfl::Description<"Height of a sprite", int>
      sprite_height;
  }; // clang-format on

  /**
   * @class TilePrefab
   * @brief Tile prefab used for JSON serialization.
   * A prefab is an entity model that is re-used throughout the world.
   *
   */
  struct TilePrefab {
    // clang-format off
    rfl::Description<"Spritesheed identifier", std::string>
      spritesheet_id;
    rfl::Description<"Row of sprite in spritesheet", int>
      sprite_row;
    rfl::Description<"Column of sprite in spritesheet", int>
      sprite_column;
    rfl::Description<"Is tile solid?", bool>
      solid;
  }; // clang-format on

  /**
   * @class TileInstance
   * @brief Tile instance used for JSON serialization
   *
   */
  struct TileInstance {
    // clang-format off
    rfl::Description<"Tile prefab identifier", std::string>
      prefab_id;
    rfl::Description<"X position", int>
      x;
  rfl::Description<"Y position", int>
      y;
  }; // clang-format on

  /**
   * @class WorldSpec
   * @brief World JSON specification
   *
   */
  struct WorldSpec {
    // clang-format off
    rfl::Description<"World width in tiles", int> 
      width;
    rfl::Description<"World height in tiles", int>
      height;
    rfl::Description<"Size of a tile", int>
      tile_size = 16;
    rfl::Description<"Sprites will be scaled by this value. Usually 2, avoid changing "
      "this", int>
      spx_multiplier = 2;
    rfl::Description<"Spritesheet declarations",
      std::map<std::string, SpritesheetSpec>>
      spritesheets;
    rfl::Description<"Prefab declarations. A prefab is an entity model that is re-used "
      "throughout the world.",
      std::map<std::string, TilePrefab>>
      tile_prefabs;
    rfl::Description<"Entities", std::vector<TileInstance>>
      tile_data;
  }; // clang-format on

  /**
   * @brief Parse JSON file to world spec
   * @param root parent folder of JSON file. Should also be the root folder of the entire
   * world's directory.
   */
  std::optional<WorldSpec> parse_world(std::filesystem::path root);

  /**
   * @brief Load world instance from world spec
   * @param spec
   * @param root root directory of the world.
   */
  std::optional<World> load_world(const WorldSpec &spec,
                                  const std::filesystem::path root);

} // namespace yumeami
namespace yumeami::impl {

  bool load_spritesheets(World &world, const WorldSpec &spec,
                         const std::filesystem::path root);
  bool load_tiles(World &world, const WorldSpec &spec);

} // namespace yumeami::impl
