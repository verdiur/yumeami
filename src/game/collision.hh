/**
 * @file collision.hh
 * @brief Collision struct
 */

#pragma once
#include "common/units.hh"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "game/components.hh"
#include <vector>

namespace yumeami {

  /**
   * @class Collision
   * @brief World collision data.
   *
   * @details the static grid is organized like so:
   * [
   *  [column]
   *  [column]
   *  ...
   * ]
   *
   */
  struct Collision {
    std::vector<std::vector<int>> static_grid;
    std::vector<entt::entity> dynamic_grid;

    int get_static_cell(tile_int x, tile_int y) const;
    int &get_static_cell(tile_int x, tile_int y);
  };

  struct CollisionTag {};

  /**
   * @brief Update collision grid with movement origin and destination
   * @param collision
   * @param from
   * @param to
   */
  void update_static_collision(Collision &collision, const TrueTilePos &from,
                               const TrueTilePos &to);

} // namespace yumeami
