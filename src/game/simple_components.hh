/**
 * @file
 * @brief Components that are only simple data structs.
 */

#pragma once
#include "util/simple_types.hh"

namespace yumeami::comp {

  /**
   * @class TrueTilePosition
   * @brief Tile position, stored as integers. Used for the entity's true position (e.g.
   * when it's not moving between two tiles).
   *
   */
  struct TrueTilePosition : public IntTilePosition
  {};

  /**
   * @class DrawTilePosition
   * @brief Tile position, stored as floats. Used for drawing the entity on the virtual
   * target.
   *
   */
  struct DrawTilePosition : public FloatTilePosition
  {};

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
   * @brief In seconds, how much time it takes to move a distance of 1 tile at
   * normal speed.
   *
   */
  struct Velocity
  {
    float velocity;
  };

  struct ControllableFlag
  {};

} // namespace yumeami::comp
