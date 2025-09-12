/**
 * @file draw_sprites.hh
 * @brief Draw functions for sprites of a world
 */

#pragma once
#include "common/raii.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "resman/texture.hh"
namespace yumeami {

  /**
   * @brief Draw all sprite-bearing entities
   * @param world
   * @param pool
   */
  void draw_sprites(World &world, SafeRenderTex &vp, SheetPool &pool);

} // namespace yumeami
namespace yumeami::impl {

  Sprite *get_sprite(World &world, entt::entity ent, float dst_x, float dst_y);

  Sheet *get_sheet(World &world, SheetPool &pool, const Sprite *sprite,
                   float dst_x, float dst_y);


  void draw_sprite_texture(World &world, const Sheet &sheet,
                           const Sprite &sprite, float dst_x, float dst_y);
  void draw_fallback_no_sprite(World &world, float dst_x, float dst_y);
  void draw_fallback_no_sheet(World &world, float dst_x, float dst_y);

  /**
   * @brief Tells you if a sprite is off camera. Off camera means that at least
   * part of the sprite is off camera.
   *
   */
  bool is_sprite_off_camera(const World &world, const SafeRenderTex &vp,
                            const Sheet *sheet, float dst_x, float dst_y);

  /**
   * @brief Draw a single sprite, with fallback drawing. Basically just chooses
   * between draw_sprite_texture, draw_fallback_no_sprite and
   * draw_fallback_no_sheet
   *
   */
  void draw_sprite(World &world, const Sheet *sheet, const Sprite *sprite,
                   float dst_x, float dst_y);

  /**
   * @brief Draw a single sprite, and draw it around the visible world
   * boundaries if wrap_off_camera is true. This ensures seamless wrapped world
   * drawing by filling in the empty space to create an illusion of an infinite
   * world.
   *
   */
  void draw_sprite_wrap(World &world, const Sheet *sheet, const Sprite *sprite,
                        float dst_x, float dst_y, bool wrap_off_camera);

} // namespace yumeami::impl
