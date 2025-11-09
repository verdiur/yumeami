#pragma once
#include "common/defines.hh"
#include "model/components/common.hh"
#include <variant>
namespace yumeami {

  struct MovementStateIdle {};
  struct MovementStateMoving {
    float progress;
  };
  using MovementState = std::variant<MovementStateIdle, MovementStateMoving>;

  /**
   * @class MovementData
   * @brief Component containing current movement-related data
   *
   */
  struct MovementData YUMEAMI_COMPONENT {
    TrueTilePos src = {0, 0};
    TrueTilePos dst = {0, 0};
    MovementState state;
  };

} // namespace yumeami
