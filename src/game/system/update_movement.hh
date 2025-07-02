#pragma once
#include "entt/entt.hpp"
#include "game/component/movement_state.hh"

namespace yumeami::s {
namespace impl {

  /**
   * @brief Run a movement state machine
   *
   * @param state current state
   */
  void run_movement_state_machine(c::MovementState& state);

} // namespace impl

/**
 * @brief Updates movement of all entities.
 *
 * @param reg
 */
void
update_movement(entt::registry& registry);

} // namespace yumeami::s
