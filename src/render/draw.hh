#include "logic/components.hh"
#include "logic/world.hh"
#include "resman/texture.hh"
namespace yumeami {

  void draw_sprites(World &world, SheetPool &pool);
  void draw_world(World &world, SheetPool &pool);

} // namespace yumeami
namespace yumeami::impl {

  Sprite *get_sprite_or_fallback(World &world, entt::entity ent, float dst_x,
                                 float dst_y);

  Sheet *get_sheet_or_fallback(World &world, SheetPool &pool,
                               const Sprite &sprite, float dst_x, float dst_y);

  void draw_sprite_texture(World &world, const Sheet &sheet,
                           const Sprite &sprite, float dst_x, float dst_y);

} // namespace yumeami::impl
