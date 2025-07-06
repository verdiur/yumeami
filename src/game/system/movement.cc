#include "game/system/movement.hh"
#include "game/component/movement_state.hh"
#include "game/component/simple_components.hh"
#include "game/event/input.hh"
#include "raylib.h"
#include "util/simple_functions.hh"
#include "util/simple_types.hh"

/* BEGIN STATE MACHINE IMPLEMENTATION ***************************************************/

void
yumeami::movement_state_machine(comp::MovementState& movement_state,
                                comp::TrueTilePosition& true_tile_position,
                                comp::DrawTilePosition& draw_tile_position,
                                comp::Facing& facing,
                                comp::Velocity& velocity,
                                comp::KeyboardKeyQueue& keyboard_key_queue)
{
  using enum MovementStateEnum;

  // initialize state
  movement_state.state = BEGIN;

  // run state machine
  while (movement_state.state != END) {
    switch (movement_state.state) {

      case BEGIN: {
        movement_state.state = IS_MOVING;
      }

      case IS_MOVING: {
        if (movement_state.is_moving) {
          movement_state.state = MOVE;
        } else {
          movement_state.state = READ_EVENT_QUEUE;
        }
      }

      case READ_EVENT_QUEUE: {
        KeyboardKey key = keyboard_key_queue.consume();

        // end state machine if no keys pressed
        if (key == KEY_NULL) {
          movement_state.state = END;
          break;
        }

        // update facing
        if (key == KEY_DOWN) {
          facing.direction = Direction4::DOWN;
        } else if (key == KEY_UP) {
          facing.direction = Direction4::UP;
        } else if (key == KEY_LEFT) {
          facing.direction = Direction4::LEFT;
        } else if (key == KEY_RIGHT) {
          facing.direction = Direction4::RIGHT;
        }
        movement_state.state = CHECK_COLLISION;
      }

      case CHECK_COLLISION: { // TODO:
        movement_state.state = CHECK_OOB;
      }

      case CHECK_OOB: { // TODO:
        movement_state.state = CHECK_WRAP;
      }

      case CHECK_WRAP: { // TODO:
        movement_state.state = UPDATE_TILE_POSITIONS;
      }

      case UPDATE_TILE_POSITIONS: {
        // calculate targeted position
        IntTilePosition target_int =
          calculate_int_position_from_facing(facing, true_tile_position);
        FloatTilePosition target_float =
          calculate_float_position_from_facing(facing, draw_tile_position);

        // update positions
        true_tile_position = static_cast<comp::TrueTilePosition>(target_int);
        movement_state.from = draw_tile_position;
        movement_state.to = target_float;
        movement_state.state = BEGIN_MOVING;
      }

      case BEGIN_MOVING: {
        movement_state.is_moving = true;
        movement_state.state = MOVE;
      }

      case MOVE: {
        // TODO: interpolate instead
        draw_tile_position = static_cast<comp::DrawTilePosition>(movement_state.to);
        movement_state.progress = 1;
        movement_state.state = STOP_MOVING_IF_FINISHED;
      }

      case STOP_MOVING_IF_FINISHED: {
        if (movement_state.progress >= 1) {
          // snap draw position
          draw_tile_position = static_cast<comp::DrawTilePosition>(movement_state.to);
          bool is_moving = false;
        }
        movement_state.state = END;
      }

      case END: {
        break;
      }
    }
  }
}

/* END STATE MACHINE IMPLEMENTATION *****************************************************/

void
yumeami::sys::update_movement(entt::registry& registry)
{
  auto view = registry.view<comp::MovementState,
                            comp::TrueTilePosition,
                            comp::DrawTilePosition,
                            comp::Facing,
                            comp::Velocity,
                            comp::KeyboardKeyQueue>();
  for (auto [entity,
             movement_state,
             true_tile_position,
             draw_tile_position,
             facing,
             velocity,
             keyboard_key_queue] : view.each()) {
    movement_state_machine(movement_state,
                           true_tile_position,
                           draw_tile_position,
                           facing,
                           velocity,
                           keyboard_key_queue);
  }
}
