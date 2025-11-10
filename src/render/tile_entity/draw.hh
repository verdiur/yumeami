#pragma once
#include "model/viewport/fwd.hh"
#include "model/world/fwd.hh"
namespace yumeami {

  /**
   * @brief Draw entities with a DrawTilePos component
   * @param world
   * @param vp
   */
  void draw_tile_entities(World &world, Viewport &vp);

} // namespace yumeami
