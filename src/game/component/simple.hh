/**
 * @file
 * @brief Components that are only simple structs.
 */

#pragma once
#include "util/units.hh"

/**
 * @namespace c
 * @brief Namespace containing components. Abbreviated to "c" for convenience, as
 * components are used extensively.
 */
namespace yumeami::c {

/**
 * @class TrueTilePos
 * @brief Tile position, stored as integers. Used for the entity's true position (e.g.
 * when it's not moving between two tiles).
 *
 */
struct TrueTilePosition
{
  tile_int x;
  tile_int y;
};

/**
 * @class DrawTilePos
 * @brief Tile position, stored as floats. Used for drawing the entity on the virtual
 * target.
 *
 */
struct DrawTilePosition
{
  tile_float x;
  tile_float y;
};

/**
 * @class DrawSortKey
 * @brief Read-only component used to sort entity drawing.
 *
 * TODO: also sort based on layers.
 *
 */
struct DrawSortKey
{
  const DrawTilePosition* draw_tile_position;
};

} // namespace yumeami::c
