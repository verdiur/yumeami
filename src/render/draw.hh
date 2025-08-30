#include "assetmgr/texture.hh"
#include "logic/components.hh"
#include "logic/world.hh"
namespace yumeami {

  void draw_sprites(World &world, SheetPool &pool);
  void draw_world(World &world, SheetPool &pool);

} // namespace yumeami
namespace yumeami::impl {

  std::optional<Sprite> get_sprite_or_fallback(World &world, entt::entity ent,
                                               float dst_x, float dst_y);

  std::optional<std::shared_ptr<Sheet>>
  get_sheet_or_fallback(World &world, const SheetPool &pool,
                        const Sprite &sprite, float dst_x, float dst_y);

  void draw_sprite_texture(
      World &world, const std::optional<std::shared_ptr<Sheet>> opt_sheet_ptr,
      const std::optional<Sprite> opt_sprite, float dst_x, float dst_y);

} // namespace yumeami::impl
