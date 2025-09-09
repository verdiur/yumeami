#pragma once
#include "common/raii.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "resman/texture.hh"
namespace yumeami {

  enum struct DrawSpriteStatus {
    OK = 0,
    NO_SPRITE,
    NO_SHEET,
  };

  /**
   * @brief Draw all sprite-bearing entities
   * @param world
   * @param pool
   */
  void draw_sprites(World &world, SafeRenderTex &vp, SheetPool &pool);

} // namespace yumeami
namespace yumeami::impl {

  Sprite *get_sprite(World &world, entt::entity ent, float dst_x, float dst_y,
                     DrawSpriteStatus &status);

  Sheet *get_sheet(World &world, SheetPool &pool, const Sprite *sprite,
                   float dst_x, float dst_y, DrawSpriteStatus &status);

  /**
   * @brief Tells you if a sprite is off camera. Off camera means that at least
   * part of the sprite is off camera.
   *
   */
  bool is_sprite_off_camera(const World &world, const SafeRenderTex &vp,
                            const Sheet *sheet, float dst_x, float dst_y);

  void draw_sprite_texture(World &world, const Sheet &sheet,
                           const Sprite &sprite, float dst_x, float dst_y);

  void draw_fallback_no_sprite(World &world, float dst_x, float dst_y);
  void draw_fallback_no_sheet(World &world, float dst_x, float dst_y);

} // namespace yumeami::impl
