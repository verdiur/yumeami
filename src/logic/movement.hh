/**
 * @file movement.hh
 * @brief Movement updates and event handling
 */

#pragma once
#include "common/direction.hh"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "entt/signal/fwd.hpp"
#include "logic/components.hh"
#include "logic/world.hh"
#include <optional>
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
  void update_movement_state(World &world);

} // namespace yumeami
namespace yumeami::impl {

  /**
   * @class MovementComponents
   * @brief Simple container for all components used for movement
   *
   */
  struct MovementComponents {
    TruePos *true_pos;
    DrawPos *draw_pos;
    MovementState *movement_state;
    Facing *facing;
    Velocity *velocity;
    bool has_collision;
  };

  /**
   * @class MovementCoords
   * @brief A pair of movement source and destination coordinates.
   *
   */
  struct MovementCoords {
    TruePos src;
    TruePos dst;
  };

  bool movement_tgt_exists(const MovementEvent &event);

  std::optional<MovementComponents>
  movement_get_components(const MovementEvent &event);

  bool movement_is_moving(const MovementComponents &components);
  void movement_try_update_facing(const MovementEvent &event,
                                  MovementComponents &components);

  bool movement_collides(const MovementEvent &event,
                         const MovementComponents &components);

  /**
   * @brief Calculates movement source and destination. Destination might be out
   * of bounds.
   *
   * @param event
   * @param components
   * @return movement coordinates
   */
  MovementCoords movement_calc_raw_coords(const MovementEvent &event,
                                          const MovementComponents &components);

  /**
   * @brief Calculates wrapped destination and ADJUSTED SOURCE. The source
   * position will always be 1 tile behind the destination, so it might end up
   * out of bounds. To access the actual modulo'd coordinates:
   * - src should be from the raw coords;
   * - dst should be from the wrapped coords.
   *
   * @param event
   * @param raw
   * @return "wrapped" movement coordinates
   */
  MovementCoords
  movement_calc_wrapped_dst_and_adjust_src(const MovementEvent &event,
                                           const MovementCoords &raw);

  bool movement_is_oob(const MovementEvent &event,
                       const MovementComponents &components);

  /**
   * @brief Apply some movement coordinates to the movement state component.
   * @param coord
   * @param components
   */
  void movement_set_coords(MovementCoords &coord,
                           MovementComponents &components);

  void movement_begin(MovementComponents &components);

} // namespace yumeami::impl
