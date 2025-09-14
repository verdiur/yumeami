/**
 * @file draw_debug.hh
 * @brief Debug-related draw functions
 */

#pragma once
#include "logic/world.hh"
namespace yumeami {

  void draw_debug_info(int text_size);
  void draw_debug_collision(const World &world);
  void draw_debug_world_bounds(const World &world);
  void draw_debug_facing(const World &world, float arrow_length);

} // namespace yumeami
