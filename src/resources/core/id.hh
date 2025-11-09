#pragma once
#include "entt/core/fwd.hpp"
namespace yumeami {

  /**
   * @brief Generate a new unique ID.
   *
   * @details This function works without a generator class, but the counterpart
   * of it is that it's not possible to reset its internal ID counter. This
   * should be fine for most use cases as the integer limit of entt::id_type
   * most likely far exceeds the amount of resources that will be loaded during
   * the lifetime of the process.
   */
  entt::id_type generate_id();

} // namespace yumeami
