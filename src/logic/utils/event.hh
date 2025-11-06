#pragma once
#include "model/world/fwd.hh"
#include <concepts>
#include <entt/entity/fwd.hpp>
#include <entt/signal/fwd.hpp>
#include <string_view>
namespace yumeami {

  /**
   * @brief Requires T to have a World pointer and an entt::dispatcher pointer.
   *
   * @tparam T
   */
  template <class T>
  concept IsEvent = requires(T t) {
    { t.world } -> std::convertible_to<World *>;
    { t.dispatcher } -> std::convertible_to<entt::dispatcher *>;
  };

  /**
   * @brief Check if the members of an event is valid.
   * @param event
   * @return true if event is valid
   */
  template <class E>
    requires IsEvent<E>
  bool is_event_valid(E event) {
    bool world_check = (event.world != nullptr);
    bool dispatcher_check = (event.dispatcher != nullptr);
    return world_check && dispatcher_check;
  }

  /**
   * @brief Check if an entity of an event exists
   * @param world
   * @return true if entity is in world registry
   */
  bool event_entity_exists(World *world, const entt::entity ent,
                           const std::string_view log_prefix);

} // namespace yumeami
