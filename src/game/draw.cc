#include "game/draw.hh"
#include "game/components.hh"
#include "game/world.hh"
#include "raylib.h"


void yumeami::draw_registry(World &world, RenderTexture &viewport) {
  auto view = world.registry.view<DrawTilePos>();
  for (auto [entity, draw_pos] : view.each()) {
    // TODO: this implementation is placeholder
    DrawRectangle(draw_pos.x * world.tile_size * world.spritepx_multiplier,
                  draw_pos.y * world.tile_size * world.spritepx_multiplier,
                  world.tile_size * world.spritepx_multiplier,
                  world.tile_size * world.spritepx_multiplier, WHITE);
  }
}


void yumeami::draw_world(World &world, RenderTexture &viewport) {
  update_camera(world, viewport);
  BeginMode2D(world.camera);

  draw_registry(world, viewport);
  // will add more in the future...

  EndMode2D();
}
