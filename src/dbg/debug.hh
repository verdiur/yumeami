/**
 * @file debug.hh
 * @brief Functions for debugging
 */

#pragma once
#include "game/world.hh"

namespace yumeami::debug {
  World create_player_test_world();
  World create_spritesheet_test_world();
  World create_collision_test_world();
  std::optional<World> load_test_world();
} // namespace yumeami::debug
