/**
 * @file components.hh
 * @brief Common components
 */

#pragma once
#include "common/defines.hh"
#include "common/direction.hh"
#include "common/units.hh"
namespace yumeami {

  struct TruePos YUMEAMI_COMPONENT {
    tile x;
    tile y;
  };

  struct DrawPos YUMEAMI_COMPONENT {
    tile x;
    tile y;
  };

  struct PixelPos YUMEAMI_COMPONENT {
    float x;
    float y;
  };

  struct Velocity YUMEAMI_COMPONENT {
    float vel; // time in seconds that it takes to move 1 tile.
    operator float() const { return vel; }
  };

  struct Facing YUMEAMI_COMPONENT {
    Direction dir;
    operator Direction() const { return dir; }
  };

  struct Sprite YUMEAMI_COMPONENT {
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
  struct PlayerTag YUMEAMI_COMPONENT{};

  /**
   * @class CollisionTag
   * @brief Marks a collidable entity.
   *
   */
  struct CollisionTag YUMEAMI_COMPONENT{};

  /**
   * @class CameraTargetTag
   * @brief Marks a camera target. the entity with this tag will be targeted by
   * the camera. if multiple entities have this tag, the first found entity will
   * be targeted, and the others will be ignored.
   *
   */
  struct CameraTargetTag YUMEAMI_COMPONENT{};

} // namespace yumeami
