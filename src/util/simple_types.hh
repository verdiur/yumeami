#pragma once
#include "util/units.hh"

namespace yumeami {

  enum class Direction4
  {
    BOTTOM = 0,
    TOP,
    LEFT,
    RIGHT
  };

  enum class Direction8
  {
    BOTTOM = 0,
    TOP,
    LEFT,
    RIGHT,
    BOTTOM_LEFT,
    TOP_LEFT,
    BOTTOM_RIGHT,
    TOP_RIGHT
  };

  struct FloatTilePosition
  {

    tile_float x;
    tile_float y;
  };

  struct IntTilePosition
  {
    tile_int x;
    tile_int y;
  };

} // namespace yumeami
