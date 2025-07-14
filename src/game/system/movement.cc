#include "game/system/movement.hh"
#include "game/event/simple_events.hh"
#include "game/event/simple_queues.hh"
#include "game/simple_components.hh"
#include "game/system/movement.hh"
#include "raylib.h"
#include "util/simple_functions.hh"
#include "util/simple_types.hh"
#include <cmath>
#include <optional>

/* BEGIN STATE MACHINE IMPLEMENTATION ***************************************************/

void
yumeami::movement_state_machine(comp::Movement& movement,
                                comp::TrueTilePosition& true_tile_position,
                                comp::DrawTilePosition& draw_tile_position,
                                comp::Facing& facing,
                                comp::Velocity& velocity,
                                comp::MoveEventQueue& move_event_queue)
{
  using enum MovementState;

  // initialize state
  movement.state = BEGIN;

  // run state machine
  while (movement.state != END) {
    switch (movement.state) {

      case BEGIN: {
        movement.state = IS_MOVING;
        break;
      }

      case IS_MOVING: {
        if (movement.is_moving) {
          movement.state = MOVE;
        } else {
          movement.state = READ_EVENT_QUEUE;
        }
        break;
      }

      case READ_EVENT_QUEUE: {
        std::optional<event::MoveEvent> event = move_event_queue.consume();

        // end state machine if queue is empty
        if (!event.has_value()) {
          movement.state = END;
          break;
        }

        // update facing and state
        facing.direction = event.value().direction;
        movement.state = CHECK_COLLISION;
        break;
      }

      case CHECK_COLLISION: { // TODO:
        movement.state = CHECK_OOB;
        break;
      }

      case CHECK_OOB: { // TODO:
        movement.state = CHECK_WRAP;
        break;
      }

      case CHECK_WRAP: { // TODO:
        movement.state = UPDATE_TILE_POSITIONS;
        break;
      }

      case UPDATE_TILE_POSITIONS: {
        // calculate targeted position
        IntTilePosition target_int =
          calculate_int_position_from_facing(facing, true_tile_position);
        FloatTilePosition target_float =
          calculate_float_position_from_facing(facing, draw_tile_position);

        // update positions
        true_tile_position = static_cast<comp::TrueTilePosition>(target_int);
        movement.from = draw_tile_position;
        movement.to = target_float;
        movement.state = BEGIN_MOVING;
        break;
      }

      case BEGIN_MOVING: {
        movement.is_moving = true;
        movement.state = MOVE;
        break;
      }

      case MOVE: {
        movement.progress += (1 / velocity.velocity) * GetFrameTime();
        draw_tile_position.x =
          std::lerp(movement.from.x, movement.to.x, movement.progress);
        draw_tile_position.y =
          std::lerp(movement.from.y, movement.to.y, movement.progress);

        movement.state = STOP_MOVING_IF_FINISHED;
        break;
      }

      case STOP_MOVING_IF_FINISHED: {
        if (movement.progress >= 1) {
          // snap draw position
          draw_tile_position = static_cast<comp::DrawTilePosition>(movement.to);
          movement.progress = 0;
          movement.is_moving = false;
        }
        movement.state = END;
        break;
      }

      case END: {
        // if everything goes well the contents of this state should never be executed
        break;
      }
    }
  }
  move_event_queue.clear();
}

/* END STATE MACHINE IMPLEMENTATION *****************************************************/

void
yumeami::sys::update_movement(entt::registry& registry)
{
  auto view = registry.view<comp::Movement,
                            comp::TrueTilePosition,
                            comp::DrawTilePosition,
                            comp::Facing,
                            comp::Velocity,
                            comp::MoveEventQueue>();
  for (auto [entity,
             movement,
             true_tile_position,
             draw_tile_position,
             facing,
             velocity,
             move_event_queue] : view.each()) {
    movement_state_machine(movement,
                           true_tile_position,
                           draw_tile_position,
                           facing,
                           velocity,
                           move_event_queue);
  }
}

void
yumeami::sys::setup_connect_move_events(entt::dispatcher& dispatcher,
                                        entt::registry& registry)
{
  auto view = registry.view<comp::MoveEventQueue>();
  for (auto [entity, move_event_queue] : view.each()) {
    dispatcher.sink<event::MoveEvent>().connect<&comp::MoveEventQueue::receive>(
      move_event_queue);
  }
}
