/**
 * @file movement.hh
 * @brief Movement-related stuff
 */

#pragma once
#include "entt/fwd.hpp"
#include "game/world.hh"
#include "util/direction.hh"

namespace yumeami {

  // State of movement state machine
  enum struct MovementState { IDLE = 0 };

  /**
   * @class Movement
   * @brief Movement component. Encapsulates all information about the entity's movement.
   * An entity cannot move it doesn't have this component.
   *
   */
  struct Movement {
    MovementState state; // current state
    bool is_moving;      // true if entity is performing a movement
  };

  struct MoveEvent {
    entt::entity target;  // targeted entity
    World *world;         // world ctx
    Direction4 direction; // direction of movement
  };

  /**
   * @brief Handle a move event. Does collision, OOB, wrap and movement checks, and
   * triggers movement if checks pass.
   *
   * @param event
   */
  void handle_move_event(const MoveEvent &event);

  /**
   * @brief Connect move events to dispatcher
   * @param dispatcher
   */
  void setup_dispatcher_movement(entt::dispatcher &dispatcher);

  /**
   * @brief Update movement for concerned entities. Runs a state machine internally.
   * @param world
   */
  void update_movement(World &world);

} // namespace yumeami
