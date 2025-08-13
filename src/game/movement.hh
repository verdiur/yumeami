/**
 * @file movement.hh
 * @brief Movement-related stuff
 */

#pragma once
#include "entt/entity/fwd.hpp"
#include "entt/fwd.hpp"
#include "game/components.hh"
#include "game/world.hh"
#include "util/direction.hh"

namespace yumeami {

  /**
   * @class Movement
   * @brief Movement component. Encapsulates all information about the entity's movement.
   * An entity cannot move it doesn't have this component.
   *
   */
  struct Movement {
    bool is_moving = false; // true if entity is performing a movement
    float progress = 0;     // movement progress through lerp
    TrueTilePos from = {};
    TrueTilePos to = {};
  };

  struct MoveEvent {
    entt::entity target;  // targeted entity
    World *world;         // world ctx
    Direction4 direction; // direction of movement
  };

  /**
   * @brief Handle a move event. Does collision, OOB, wrap and movement checks, and
   * sets up + triggers movement if checks pass.
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
   * @brief Update position of applicable entities. This function is not concerned with
   * movement logic; this is implemented in handler functions. (DrawTilePos, TrueTilePos,
   * Velocity, Movement)
   * @param world
   */
  void update_movement(World &world);

} // namespace yumeami
namespace yumeami::impl {
  bool move_event_destination_is_oob(const World &world, const TrueTilePos &destination);
}
