/**
 * @file conversions.hh
 * @brief Type conversion functions
 */

#pragma once

#include "common/direction.hh"
#include "game/components.hh"

namespace yumeami {

  DrawTilePos to_draw_tile_pos(TrueTilePos true_pos);
  TrueTilePos to_true_tile_pos(DrawTilePos draw_pos); // avoid using this
  TrueTilePos calc_true_tile_pos_from_direction4(TrueTilePos true_pos,
                                                 Direction4 direction);

} // namespace yumeami
