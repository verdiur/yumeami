/**
 * @file draw_sprites.hh
 * @brief Draw functions for sprites of a world
 */

#pragma once
#include "common/raii.hh"
#include "logic/world.hh"
#include "resman/spritesheet.hh"
namespace yumeami {

  /**
   * @brief Draw all sprite-bearing entities
   * @param world
   * @param pool
   */
  void draw_sprites(World &world, SafeRenderTex &vp, SheetCache &cache);

} // namespace yumeami
