/**
 * @file collision.hh
 * @brief Collision struct
 */

#pragma once
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "game/components.hh"
#include "util/units.hh"
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

  void update_static_collision(Collision &collision, const TrueTilePos &from,
                               const TrueTilePos &to);

} // namespace yumeami
