/**
 * @file components.hh
 * @brief Common component structs
 */

#pragma once
#include "raylib.h"
#include "util/direction.hh"
#include "util/units.hh"

namespace yumeami {

  /**
   * @class TrueTilePos
   * @brief Tile position stored as ints. Denotes internal position.
   *
   */
  struct TrueTilePos {
    tile_int x, y;
  };

  /**
   * @class DrawTilePos
   * @brief Tile position stored as floats. Used to draw the entity.
   *
   */
  struct DrawTilePos {
    tile_float x, y;
  };

  /**
   * @class Velocity
   * @brief Corresponds to the time it takes to move a distance of 1 tile, in seconds.
   *
   */
  struct Velocity {
    float vel;
  };

  /**
   * @class Facing
   * @brief Facing direction of entity.
   *
   */
  struct Facing {
    Direction4 fac;
  };

  /**
   * @class Sprite
   * @brief Simple sprite component. Might abstract this further later
   * TODO: yes please do abstract it further it will be needed
   *
   */
  struct Sprite {
    Texture tex;
  };

  /* TAGS *******************************************************************************/

  struct PlayerTag {};

} // namespace yumeami
