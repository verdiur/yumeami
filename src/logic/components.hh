/**
 * @file components.hh
 * @brief Common components
 */

#pragma once
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

  struct Sprite {
    std::string sheet_id;
    int row;
    int col;
  };

  /* TAGS ********************************************************************/

  struct PlayerTag {};
  struct CollisionTag {};

} // namespace yumeami
