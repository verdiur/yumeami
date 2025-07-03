#include "game/system/movement.hh"
#include "game/component/movement_state.hh"
#include "game/component/simple_components.hh"
#include "util/simple_functions.hh"
#include "util/simple_types.hh"

namespace yumeami::s {

namespace impl {

  void run_movement_state_machine(c::MovementState& movement_state,
                                  c::TrueTilePosition& true_tile_position,
                                  c::DrawTilePosition& draw_tile_position,
                                  c::Facing& facing,
                                  c::Velocity velocity)
  {
    using enum MovementStateEnum;

    // run state machine
    while (movement_state.state != END) {
      switch (movement_state.state) {

        case BEGIN:
          movement_state.state = IS_MOVE_FINISHED;

        case IS_MOVE_FINISHED:
          // TODO: implementation details
          if (movement_state.progress > 1) {
            movement_state.state = READ_EVENT_QUEUE;
          } else {
            movement_state.state = MOVE;
          }

        case READ_EVENT_QUEUE:
          // TODO: implement events...
          movement_state.state = CHECK_COLLISION;

        case CHECK_COLLISION:
          movement_state.state = CHECK_OOB;

        case CHECK_OOB:
          movement_state.state = CHECK_WRAP;

        case CHECK_WRAP:
          movement_state.state = UPDATE_TILE_POSITIONS;

        case UPDATE_TILE_POSITIONS: {

          // calculate targeted position
          IntTilePosition target_int =
            calculate_facing_int_position(facing, true_tile_position);

          FloatTilePosition target_float =
            calculate_facing_float_position(facing, true_tile_position);

          // update positions
          // NOTE: static casts might be bad?
          true_tile_position = static_cast<c::TrueTilePosition>(target_int);
          movement_state.from = static_cast<c::DrawTilePosition>(target_float);
          movement_state.to = static_cast<c::DrawTilePosition>(target_float);
        };
          movement_state.state = MOVE;

        case MOVE:
          // do something...
          movement_state.state = END;

        case END:
          break;
      }
    }
  }

} // namespace impl

void
update_movement(entt::registry& registry)
{
  auto view = registry.view<c::MovementState,
                            c::TrueTilePosition,
                            c::DrawTilePosition,
                            c::Facing,
                            c::Velocity>();
  for (auto [entity,
             movement_state,
             true_tile_position,
             draw_tile_position,
             facing,
             velocity] : view.each()) {
    run_movement_state_machine(
      movement_state, true_tile_position, draw_tile_position, facing, velocity);
  }
}

} // namespace yumeami::s
