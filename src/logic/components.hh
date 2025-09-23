/**
 * @file components.hh
 * @brief Common components
 */

#pragma once
#include "common/direction.hh"
#include "common/units.hh"
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
    int sheet_id;
    int row;
    int col;
  };

  /* TAGS ********************************************************************/

  /**
   * @class PlayerTag
   * @brief Marks a playable entity. An entity with this tag will receive player
   * input.
   *
   */
  struct PlayerTag {};

  /**
   * @class CollisionTag
   * @brief Marks a collidable entity.
   *
   */
  struct CollisionTag {};

  /**
   * @class CameraTargetTag
   * @brief Marks a camera target. the entity with this tag will be targeted by
   * the camera. if multiple entities have this tag, the first found entity will
   * be targeted, and the others will be ignored.
   *
   */
  struct CameraTargetTag {};

} // namespace yumeami
