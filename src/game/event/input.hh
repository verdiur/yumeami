#pragma once
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "entt/signal/fwd.hpp"

namespace yumeami {

  struct KeyboardKeyMappings
  {};

  namespace sys {
    /**
     * @brief Look for input and send events accordingly
     *
     * @param dispatcher
     */
    void dispatch_input_events(entt::registry& registry, entt::dispatcher& dispatcher);

  } // namespace sys

} // namespace yumeami
