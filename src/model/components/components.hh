#pragma once
#include "common/types/direction.hh"
#include "common/types/vector.hh"
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
    operator float &() { return vel; }
  };

  struct Facing {
    Direction dir;
    operator Direction &() { return dir; }
  };

  /* TAGS *********************************************************************/

  struct PlayerTag {};
  struct CollisionTag {};
  struct CameraTargetTag {};

} // namespace yumeami
