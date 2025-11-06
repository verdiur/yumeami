#pragma once
#include "common/types/direction.hh"
#include "model/world/fwd.hh"
#include <entt/entity/fwd.hpp>
#include <entt/signal/fwd.hpp>
namespace yumeami {

  /**
   * @class EntityMoveCommand
   * @brief Event that requests an entity to move (if applicable)
   *
   */
  struct EntityMoveCommand {
    World *world;
    entt::dispatcher *dispatcher;
    entt::entity target;
    Direction direction;
  };

  /**
   * @class EntityMoveStartEvent
   * @brief Event that indicates that an entity starts moving
   *
   */
  struct EntityMoveStartEvent {
    World *world;
    entt::dispatcher *dispatcher;
    entt::entity sender;
  };

  /**
   * @class EntityMoveEndEvent
   * @brief Event that indicates that an entity has finished moving
   *
   */
  struct EntityMoveFinishEvent {
    World *world;
    entt::dispatcher *dispatcher;
    entt::entity sender;
  };

  /**
   * @brief Setup dispatcher for movement
   * @param dispatcher
   */
  void setup_dispatcher_movement(entt::dispatcher &dispatcher);

  /**
   * @brief Movement event handler. Does multiple checks and if they pass,
   * triggers movement for target. An EntityMoveStartEvent will be fired.
   * @details The following checks are performed:
   * - Target existence
   * - Does the target have the necessary components?
   * - If facing component is present, update facing. This will occur even if
   * movement is blocked.
   * - Collision, out of bounds, wrap
   *
   * @param event
   */
  void handle_entity_move_command(const EntityMoveCommand &cmd);

  /**
   * @brief Update all entity movement in world. Also fires an
   * EntityMoveFinishEvent for each entity that has finished moving.
   * @param world
   * @param dispatcher
   */
  void update_movement_state(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
