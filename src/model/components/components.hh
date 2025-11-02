#pragma once
#include "common/defines.hh"
#include "common/types/direction.hh"
#include "common/types/vector.hh"
namespace yumeami {

  YUMEAMI_COMPONENT struct TrueTilePos {
    TileVector2 pos;
  };

  YUMEAMI_COMPONENT struct DrawTilePos {
    TileVector2 pos;
  };

  YUMEAMI_COMPONENT struct TexelPos {
    TexelVector2 pos;
  };

  YUMEAMI_COMPONENT struct Velocity {
    float vel;
  };

  YUMEAMI_COMPONENT struct Facing {
    Direction dir;
  };

  /* TAGS *********************************************************************/

  YUMEAMI_COMPONENT struct PlayerTag {};
  YUMEAMI_COMPONENT struct CollisionTag {};
  YUMEAMI_COMPONENT struct CameraTargetTag {};

} // namespace yumeami
