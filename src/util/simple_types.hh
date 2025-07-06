#pragma once
#include "util/units.hh"

namespace yumeami {

  enum class Direction4
  {
    DOWN = 0,
    UP,
    LEFT,
    RIGHT
  };

  enum class Direction8
  {
    DOWN = 0,
    UP,
    LEFT,
    RIGHT,
    DOWN_LEFT,
    UP_LEFT,
    DOWN_RIGHT,
    UP_RIGHT
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
