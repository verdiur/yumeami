/**
 * @file draw_background.hh
 * @brief Draw functions for world background
 */

#pragma once
#include "common/raii.hh"
#include "logic/world.hh"
#include "resman/texture.hh"
namespace yumeami {

  /**
   * @brief Draw background of world
   * @param world
   * @param vp
   * @param cache
   */
  void draw_background(World &world, SafeRenderTex &vp, TextureCache &cache);

} // namespace yumeami
