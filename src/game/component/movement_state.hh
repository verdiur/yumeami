#pragma once

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
  UPDATE_TRUE_TILE_POSITION,
  MOVE,
};

namespace c {

  /**
   * @class MovementState
   * @brief Component storing movement state.
   *
   */
  struct MovementState
  {
    MovementStateEnum state;
  };

} // namespace c

} // namespace yumeami
