#pragma once
#include "entt/entt.hpp"
#include "game/component/movement_state.hh"
#include "game/component/simple_components.hh"

namespace yumeami {

/**
 * @brief Run a movement state machine
 *
 * @param state current state
 */
void
run_movement_state_machine(c::MovementState& movement_state,
                           c::TrueTilePosition& true_tile_position,
                           c::DrawTilePosition& draw_tile_position,
                           c::Facing& facing,
                           c::Velocity velocity);

namespace s {

  /**
   * @brief Updates movement of all moving entities.
   *
   * @param reg
   */
  void update_movement(entt::registry& registry);

} // namespace s

} // namespace yumeami
