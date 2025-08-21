#include "game/draw.hh"
#include "game/components.hh"
#include "game/texture.hh"
#include "game/world.hh"
#include "raylib.h"


/* IMPL *********************************************************************************/


void yumeami::impl::draw_error_tile(const DrawTilePos &draw_pos, const World &world,
                                    Color tint) {
  int px_tile_size = calc_px_tile_size(world);
  Rectangle rec = {draw_pos.x * px_tile_size, draw_pos.y * px_tile_size,
                   static_cast<float>(px_tile_size), static_cast<float>(px_tile_size)};

  DrawRectangleRec(rec, tint);
}


void yumeami::impl::draw_sprite(const Sprite &sprite, const DrawTilePos &draw_pos,
                                const World &world) {
  Rectangle dest = Rectangle{
      draw_pos.x * calc_px_tile_size(world),
      draw_pos.y * calc_px_tile_size(world),
      static_cast<float>(calc_px_tile_size(world)),
      static_cast<float>(calc_px_tile_size(world)),
  };

  Rectangle rec = calc_spritesheet_rec(sprite);

  DrawTexturePro(sprite.spritesheet_ptr->texture, calc_spritesheet_rec(sprite), dest,
                 Vector2{0, 0}, 0, WHITE);
}


/* PUBLIC *******************************************************************************/


void yumeami::draw_registry(World &world, RenderTexture &viewport) {
  auto view = world.registry.view<DrawTilePos>();
  for (auto [entity, draw_pos] : view.each()) {

    // fetch sprite
    auto *sprite = world.registry.try_get<Sprite>(entity);

    // fallback
    if (sprite == nullptr) {
      impl::draw_error_tile(draw_pos, world);
      continue;
    }

    impl::draw_sprite(*sprite, draw_pos, world);
  }
}


void yumeami::draw_world(World &world, RenderTexture &viewport) {
  update_camera(world, viewport);
  BeginMode2D(world.camera);

  draw_registry(world, viewport);
  // will add more in the future...

  EndMode2D();
}
