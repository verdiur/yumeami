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
  void movement_state_machine(comp::MovementState& movement_state,
                              comp::TrueTilePosition& true_tile_position,
                              comp::DrawTilePosition& draw_tile_position,
                              comp::Facing& facing,
                              comp::Velocity& velocity);

  namespace sys {

    /**
     * @brief Updates movement of all moving entities.
     *
     * @param reg
     */
    void update_movement(entt::registry& registry);

  } // namespace sys

} // namespace yumeami
