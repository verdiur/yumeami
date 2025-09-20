/**
 * @file emplace.hh
 * @brief Complex registry emplace operations
 */

#pragma once
#include "logic/world.hh"
namespace yumeami {

  /**
   * @brief Emplace ZOrder component
   * @param wstate
   * @param ent
   * @return true if all of DrawPos, Elevation, Floor are attached to the
   * entity. false otherwise.
   */
  bool emplace_zorder(WorldState &wstate, entt::entity ent);

} // namespace yumeami
