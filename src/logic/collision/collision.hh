#pragma once
#include "common/types/vector.hh"
#include "model/world/fwd.hh"
#include <entt/entity/fwd.hpp>
#include <entt/signal/fwd.hpp>
namespace yumeami {

  /**
   * @class UpdateCollisionCommand
   * @brief Event that requests an update of a collision cell.
   *
   */
  struct UpdateCollisionCommand {
    World *world;
    entt::dispatcher *dispatcher;
    TileVector2 src;
    TileVector2 dst;
  };

  /**
   * @brief Setup dispatcher for collision
   * @param dispatcher
   */
  void setup_dispatcher_collision(entt::dispatcher &dispatcher);

  /**
   * @brief Update collision grid. Decrements src position and increments dst
   * position.
   *
   * @param cmd
   */
  void handle_update_collision_command(const UpdateCollisionCommand &cmd);

} // namespace yumeami
