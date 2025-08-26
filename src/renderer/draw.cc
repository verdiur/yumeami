#include "renderer/draw.hh"
#include "logic/components.hh"
#include "raylib.h"


void yumeami::draw_sprites(World &world, SheetPool &pool) {
  auto view = world.reg.view<DrawPos, Sprite>();
  for (auto [entity, draw_pos, sprite] : view.each()) {

    float dst_x = draw_pos.x * world.tile_size * world.scale;
    float dst_y = draw_pos.y * world.tile_size * world.scale;

    auto sheet_opt = pool.get_sheet(sprite.sheet_id);
    if (!sheet_opt) {
      DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                    world.tile_size * world.scale, MAGENTA);
      continue;
    }

    spx spr_width = sheet_opt.value()->spr_width;
    spx spr_height = sheet_opt.value()->spr_height;

    Rectangle src = {
        .x = sprite.col * spr_width,
        .y = sprite.col * spr_height,
        .width = spr_width,
        .height = spr_height,
    };

    Rectangle dst = {
        .x = dst_x,
        .y = dst_y,
        .width = spr_width * world.scale,
        .height = spr_height * world.scale,
    };

    DrawTexturePro(sheet_opt.value()->tex, src, dst, {}, 0.0, WHITE);
  }
}


void yumeami::draw_world(World &world, SheetPool &pool) {
  draw_sprites(world, pool);
}
