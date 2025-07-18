#pragma once
#include "entt/entt.hpp"
#include "game/event/simple_queues.hh"
#include "game/simple_components.hh"

namespace yumeami {

  enum class MovementState
  {
    BEGIN = 0,
    END,
    IS_MOVING,
    READ_EVENT_QUEUE,
    CHECK_COLLISION, // not implemented yet
    CHECK_OOB,       // not implemented yet
    CHECK_WRAP,      // not implemented yet
    UPDATE_TILE_POSITIONS,
    BEGIN_MOVING,
    MOVE,
    STOP_MOVING_IF_FINISHED
  };

  namespace comp {
    /**
     * @class Movement
     * @brief Component storing movement data.
     *
     */
    struct Movement
    {
      MovementState state = MovementState::BEGIN; // current state of the state machine
      bool is_moving = 0;                         // true if entity is occupied moving
      float progress = 0;          // progression through movement (value from 0 to 1)
      FloatTilePosition from = {}; // position the movement starts from
      FloatTilePosition to = {};   // position the movement goes to
    };
  } // namespace comp

  /**
   * @brief Run a movement state machine
   *
   * @param state current state
   */
  void movement_state_machine(entt::entity entity,
                              comp::Movement& movement,
                              comp::TrueTilePosition& true_tile_position,
                              comp::DrawTilePosition& draw_tile_position,
                              comp::Facing& facing,
                              comp::Velocity& velocity,
                              comp::MoveEventQueue& move_event_queue);

  namespace sys {

    /**
     * @brief Setup: connect MoveEvent events to a dispatcher.
     * To be used when loading a world.
     *
     * @param dispatcher
     * @param registry
     */
    void setup_connect_move_events(entt::dispatcher& dispatcher,
                                   entt::registry& registry);

    /**
     * @brief Updates movement of all moving entities.
     *
     * @param registry
     */
    void update_movement(entt::registry& registry);
  } // namespace sys

} // namespace yumeami
