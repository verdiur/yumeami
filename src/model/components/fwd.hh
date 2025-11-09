#pragma once
#include <variant>
namespace yumeami {

  struct TrueTilePos;
  struct DrawTilePos;
  struct TexelPos;
  struct Velocity;
  struct Facing;

  struct PlayerTag;
  struct CollisionTag;
  struct CameraTargetTag;

  struct MovementStateIdle;
  struct MovementStateMoving;
  using MovementState = std::variant<MovementStateIdle, MovementStateMoving>;
  struct MovementData;

  struct Sprite;

} // namespace yumeami
