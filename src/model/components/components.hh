#pragma once
#include "common/types/direction.hh"
#include "common/types/vector.hh"
namespace yumeami {

  struct TrueTilePos {
    TileVector2 pos;
  };

  struct DrawTilePos {
    TileVector2 pos;
  };

  struct TexelPos {
    TexelVector2 pos;
  };

  struct Velocity {
    float vel;
  };

  struct Facing {
    Direction dir;
  };

  /* TAGS *********************************************************************/

  struct PlayerTag {};
  struct CollisionTag {};
  struct CameraTargetTag {};

} // namespace yumeami
