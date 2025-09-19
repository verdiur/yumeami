/**
 * @file draw_sprites.hh
 * @brief Draw functions for sprites of a world
 */

#pragma once
#include "common/raii.hh"
#include "logic/components.hh"
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
namespace yumeami::impl {

  struct DrawSpriteDst {
    float x;
    float y;
  };

  struct SpriteAndSheet {
    const Sprite *sprite;
    const Sheet *sheet;
  };

  SpriteAndSheet get_sprite_and_sheet(WorldState &wstate, SheetCache &cache,
                                      entt::entity ent);

  /**
   * @brief Draw a single sprite. Fallback if resources are missing.
   */
  void draw_one_sprite(const WorldConfig &wconfig, const SpriteAndSheet &res,
                       const DrawSpriteDst &dst, float scale);

  bool is_sprite_offcam(const WorldConfig &wconfig, const WorldState &wstate,
                        const SafeRenderTex &vp, const SpriteAndSheet &res,
                        const DrawSpriteDst &dst);

  /**
   * @brief Draw a single sprite, and draw it around the visible world
   * boundaries if wrap_off_camera is true. This ensures seamless wrapped world
   * drawing by filling in the empty space to create an illusion of an infinite
   * world.
   */
  void draw_one_sprite_wrap(const WorldConfig &wconfig,
                            const SpriteAndSheet &res, const DrawSpriteDst &dst,
                            float scale, bool wrap);

} // namespace yumeami::impl
