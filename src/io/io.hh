#pragma once

#include "game/world.hh"
#include <expected>
#include <string>
#include <vector>

namespace yumeami {

  enum struct ParseError { JSON_ERR, TEXTURE_ERR };

  struct SpritesheetSpec {
    std::string path;  // path to texture file
    int sprite_width;  // width of a sprite
    int sprite_height; // height of a sprite
  };

  struct TileSpec {
    int spritesheet_id;         // spreadsheet id
    int sprite_row_index;       // row index of tile's sprite
    int sprite_column_index;    // column index of tile's sprite
    int sprite_area_width = 1;  // tile batch area width
    int sprite_area_height = 1; // tile batch area height
    bool solid;                 // true if tile is solid
  };

  struct WorldSpec {
    int width;                                 // world width in tiles
    int height;                                // world height in tiles
    int tile_size = 16;                        // size of a tile
    int spx_multiplier = 2;                    // by how much to scale sprites
    std::vector<SpritesheetSpec> spritesheets; // spritesheets
    std::vector<TileSpec> tiles;               // tile definitions
  };

  /**
   * @brief Parse world from json string buffer
   * @param buffer
   * @return World instance
   */
  std::expected<World, ParseError> parse_world(std::string buffer);

} // namespace yumeami
namespace yumeami::impl {

  /**
   * @brief Add collision flag to entity and update collision grid.
   * Does not check if collision flag exists
   * @param collision
   * @param entity
   */
  void add_collision_flag_to_entity(World &world, const entt::entity entity);

  void add_tile_to_world_from_tilespec(World &world, const TileSpec &tile_spec, int x,
                                       int y);

} // namespace yumeami::impl
