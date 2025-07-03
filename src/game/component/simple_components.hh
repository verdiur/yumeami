/**
 * @file
 * @brief Components that are only simple data structs.
 */

#pragma once
#include "util/simple_types.hh"
#include "util/units.hh"

namespace yumeami::c {

/**
 * @class TrueTilePosition
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
 * @class DrawTilePosition
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

/**
 * @class Facing
 * @brief Direction that the entity is facing in.
 *
 */
struct Facing
{
  Direction4 direction;
};

/**
 * @class Velocity
 * @brief Will specify unit later TODO:
 *
 */
struct Velocity
{
  float velocity;
};

} // namespace yumeami::c
