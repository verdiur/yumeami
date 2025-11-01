#pragma once
#include "common/units/vector.hh"
namespace yumeami {

  struct TrueTilePos {
    TileVector2 pos;
    operator TileVector2 &() { return pos; }
  };

  struct DrawTilePos {
    TileVector2 pos;
    operator TileVector2 &() { return pos; }
  };

  struct TexelPos {
    TexelVector2 pos;
    operator TexelVector2 &() { return pos; }
  };

  struct Velocity {
    float vel;
    operator float() const { return vel; }
  };

  /* TAGS *********************************************************************/

  struct PlayerTag {};
  struct CollisionTag {};
  struct CameraTargetTag {};

} // namespace yumeami
