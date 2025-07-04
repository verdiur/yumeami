#pragma once

#include "util/simple_types.hh"

namespace yumeami {

enum class MovementStateEnum
{
  BEGIN = 0,
  END,
  IS_MOVE_FINISHED,
  READ_EVENT_QUEUE,
  CHECK_COLLISION,
  CHECK_OOB,
  CHECK_WRAP, // not implemented yet
  UPDATE_TILE_POSITIONS,
  MOVE,
};

namespace comp {

  /**
   * @class MovementState
   * @brief Component storing movement state.
   *
   */
  struct MovementState
  {
    MovementStateEnum state;     // current state of the state machine
    bool is_moving;              // true if entity is moving
    float progress = 0;          // progression through movement (value from 0 to 1)
    FloatTilePosition from = {}; // position the movement starts from
    FloatTilePosition to = {};   // position the movement goes to
  };

} // namespace comp

} // namespace yumeami
