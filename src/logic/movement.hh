/**
 * @file movement.hh
 * @brief Movement updates and event handling
 */

#pragma once
#include "common/direction.hh"
#include "entt/entity/fwd.hpp"
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
   * @brief Event that informs a targeted entity taht it should move
   *
   */
  struct MovementEvent {
    World *world;
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
  void update_movement_state(World &world);

} // namespace yumeami
namespace yumeami::impl {

  bool movement_target_exists(const World &world, entt::entity target);
  bool movement_components_exist(const TruePos *tgt_true_pos,
                                 const DrawPos *tgt_draw_pos,
                                 const MovementState *tgt_mvt_state,
                                 const Velocity *tgt_velocity);
  bool movement_facing_exists(const Facing *tgt_facing);
  bool movement_collides(const World &world, entt::entity target);
  bool movement_is_oob(const World &world, entt::entity target);
  void movement_trigger(entt::entity target, const Direction &event_dir,
                        TruePos &tgt_true_pos, MovementState &tgt_mvt_state);

} // namespace yumeami::impl
