/**
 * @file movement.hh
 * @brief Movement-related stuff
 */

#pragma once
#include "entt/fwd.hpp"
#include "game/world.hh"

namespace yumeami {

  struct MoveEvent {
    entt::entity target; // targeted entity
    World *world;        // world ctx
  };

  /**
   * @brief Handle a move event. Does collision, OOB, wrap and movement checks, and
   * triggers movement if checks pass.
   *
   * @param event
   */
  void handle_move_event(MoveEvent &event);

  /**
   * @brief Connect move events to dispatcher
   * @param dispatcher
   */
  void setup_dispatcher_move(entt::dispatcher &dispatcher);

} // namespace yumeami
