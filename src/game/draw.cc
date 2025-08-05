#include "game/draw.hh"
#include "game/components.hh"
#include "game/world.hh"
#include "raylib.h"


void yumeami::draw_registry(World &world, RenderTexture &viewport) {
  auto view = world.registry.view<DrawTilePos>();
  for (auto [entity, draw_pos] : view.each()) {

    // fetch sprite
    auto *sprite = world.registry.try_get<Sprite>(entity);

    // fallback
    if (sprite == nullptr) {
      DrawRectangle(draw_pos.x * calc_px_tile_size(world),
                    draw_pos.y * calc_px_tile_size(world), calc_px_tile_size(world),
                    calc_px_tile_size(world), MAGENTA);
      continue;
    }

    DrawTextureEx(sprite->tex,
                  Vector2{draw_pos.x * calc_px_tile_size(world),
                          draw_pos.y * calc_px_tile_size(world)},
                  0, world.spritepx_multiplier, WHITE);
  }
}


void yumeami::draw_world(World &world, RenderTexture &viewport) {
  update_camera(world, viewport);
  BeginMode2D(world.camera);

  draw_registry(world, viewport);
  // will add more in the future...

  EndMode2D();
}
