/**
 * @file movement.hh
 * @brief Movement updates and event handling.
 * @important This header does NOT define movement-related actions. For this,
 * see the logic/action/ directory.
 */

#pragma once
#include "common/direction.hh"
#include "entt/entt.hpp"
#include "logic/components.hh"
#include "logic/world.hh"
namespace yumeami {

  /**
   * @class MovementState
   * @brief Component representing current movement state
   *
   */
  struct MovementState {
    TruePos src = {0, 0};
    TruePos dst = {0, 0};
    float progress = 0;
    bool moving = false;
  };

  /**
   * @class MovementEvent
   * @brief Event that informs a targeted entity that it should move
   *
   */
  struct MovementEvent {
    World *world;
    entt::dispatcher *dispatcher;
    entt::entity target;
    Direction direction;
  };

  /**
   * @brief Connect movement events to handler
   * @param dispatcher
   */
  void setup_movement_event_dispatcher(entt::dispatcher &dispatcher);

  /**
   * @brief Movement event handler. Does multiple checks and if they pass,
   * triggers movement for target
   * @details The following checks are performed:
   * - Target existence
   * - Does the target have the necessary components?
   * - If facing component is present, update facing. This will occur even if
   * movement is blocked.
   * - Collision, out of bounds, wrap
   *
   * @param event
   */
  void handle_movement_event(const MovementEvent &event);

  /**
   * @brief Update the current movement state
   * @param world
   */
  void update_movement_state(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
