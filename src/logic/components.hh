/**
 * @file components.hh
 * @brief Common components
 */

#pragma once
#include "common/direction.hh"
#include "common/units.hh"
#include <string>
namespace yumeami {

  struct TruePos {
    tile x;
    tile y;
  };

  struct DrawPos {
    tile x;
    tile y;
  };

  struct PixelPos {
    float x;
    float y;
  };

  struct Velocity {
    float vel; // time in seconds that it takes to move 1 tile.
    operator float() const { return vel; }
  };

  struct Facing {
    Direction dir;
    operator Direction() const { return dir; }
  };

  struct Sprite {
    std::string sheet_id;
    int row;
    int col;
  };

  /* TAGS ********************************************************************/

  struct PlayerTag {};
  struct CollisionTag {};

} // namespace yumeami
