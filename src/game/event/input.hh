#pragma once
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "entt/signal/fwd.hpp"

namespace yumeami {

  struct KeyboardKeyMappings
  {};

  void dispatch_input_events(entt::dispatcher& dispatcher);

  namespace sys {

    /**
     * @brief Set up an event dispatcher for input events.
     * To be used when loading a world.
     *
     * @param dispatcher
     * @param registry
     */
    void initialize_input_event_dispatcher(entt::dispatcher& dispatcher,
                                           entt::registry& registry);
  } // namespace sys

} // namespace yumeami
