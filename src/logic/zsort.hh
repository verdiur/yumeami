/**
 * @file z_order.hh
 * @brief Implementation of elements used to make entities comparable in terms
 * of Z-order.
 */

#pragma once
#include "entt/entity/fwd.hpp"
#include "logic/components.hh"
namespace yumeami {

  /**
   * @class Elevation
   * @brief Elevation component, used to z-sort entities. Indicates the order in
   * which entities with the same y position should be drawn. The player entity
   * has an elevation of 0.
   *
   */
  struct Elevation {
    int elevation;
    operator int() const { return elevation; }
  };

  /**
   * @class ZSort
   * @brief Component that is used to z-sort components. Note that this
   * component is lenient: it does not require its pointer fields to be
   * non-null. During a comparison between two ZSort components, any value that
   * cannot be accessed due to a nullptr will be defaulted to 0.
   *
   */
  struct ZSort {
    Elevation *elevation;
    DrawPos *draw_pos;
    /**
     * @brief Comparison operator. Does not require any field to be non-null.
     * @param other
     * @return true if *this should be draw under other
     */
    bool operator<(const ZSort &other) const;
  };

  bool emplace_zsort(entt::registry &reg, entt::entity ent);

} // namespace yumeami
