#pragma once
#include "entt/entt.hpp"
#include "logic/components.hh"
#include "logic/world.hh"
namespace yumeami {

  struct UpdateCollisionEvent {
    World *world;
    TruePos src;
    TruePos dst;
  };

  /**
   * @brief Connect update collision events to dispatcher
   * @param dispatcher
   */
  void setup_dispatcher_collision(entt::dispatcher &dispatcher);

  /**
   * @brief Handle update collision event. Decrements src position and
   * increments dst position.
   *
   * @param event
   */
  void handle_update_collision_event(const UpdateCollisionEvent &event);

} // namespace yumeami
