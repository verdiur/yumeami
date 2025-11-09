#pragma once
#include "entt/core/fwd.hpp"
namespace yumeami {

  /**
   * @brief Generate a new unique ID.
   *
   * @details This function works without a generator class, but the counterpart
   * of it is that it's not possible to reset its internal ID counter. It is not
   * recommended to mix IDs generated with this function and IDs generated from
   * an entt::hashed_string.
   */
  entt::id_type generate_id();

} // namespace yumeami
