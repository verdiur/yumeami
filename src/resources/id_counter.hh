#pragma once
#include "entt/core/fwd.hpp"
#include <atomic>
namespace yumeami {

  class IdCounter {
    std::atomic<entt::id_type> counter;

  public:
    IdCounter(entt::id_type initial_value = 0);

    /**
     * @brief Retrieve current value, and then increment the counter.
     */
    entt::id_type next();
  };

} // namespace yumeami
