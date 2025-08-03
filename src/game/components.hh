/**
 * @file components.hh
 * @brief Common component structs
 */

#pragma once
#include "util/units.hh"

namespace yumeami {

  /**
   * @class TrueTilePos
   * @brief Tile position stored as ints. Denotes internal position.
   *
   */
  struct TrueTilePos {
    tile_int x, y;
  };

  /**
   * @class DrawTilePos
   * @brief Tile position stored as floats. Used to draw the entity.
   *
   */
  struct DrawTilePos {
    tile_float x, y;
  };

  /* FLAGS ******************************************************************************/

  struct PlayerFlag {};

} // namespace yumeami
