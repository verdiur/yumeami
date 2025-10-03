/**
 * @file draw_world.hh
 * @brief Highest-level draw functions for World struct
 */

#include "common/raii.hh"
#include "logic/world.hh"
#include "resman/spritesheet.hh"
#include "resman/texture.hh"
namespace yumeami {

  /**
   * @brief Draw world on viewport
   * @param world
   * @param pool
   */
  void draw_world(World &world, SheetCache &sheet_cache,
                  TextureCache &tex_cache, SafeRenderTex &vp);

} // namespace yumeami
