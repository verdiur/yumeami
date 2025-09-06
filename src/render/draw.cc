#include "render/draw.hh"
#include "logic/components.hh"
#include "raylib.h"
#include "resman/texture.hh"


/* IMPL ***********************************************************************/


yumeami::Sprite *yumeami::impl::get_sprite_or_fallback(World &world,
                                                       entt::entity ent,
                                                       float dst_x,
                                                       float dst_y) {
  Sprite *sprite = world.reg.try_get<Sprite>(ent);
  if (!sprite) {
    DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                  world.tile_size * world.scale, BLUE);
    DrawText("no\nsprite", dst_x, dst_y, 1, WHITE);
  }
  return sprite;
}


yumeami::Sheet *yumeami::impl::get_sheet_or_fallback(World &world,
                                                     SheetPool &pool,
                                                     const Sprite &sprite,
                                                     float dst_x, float dst_y) {
  Sheet *sheet = pool.get(sprite.sheet_id);
  if (!sheet) {
    DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                  world.tile_size * world.scale, MAGENTA);
    DrawText("no\nsheet", dst_x, dst_y, 1, WHITE);
  }
  return sheet;
}


void yumeami::impl::draw_sprite_texture(World &world, const Sheet &sheet,
                                        const Sprite &sprite, float dst_x,
                                        float dst_y) {
  spx spr_width = sheet.spr_width;
  spx spr_height = sheet.spr_height;

  Rectangle src = {
      .x = sprite.col * spr_width,
      .y = sprite.row * spr_height,
      .width = spr_width,
      .height = spr_height,
  };
  Rectangle dst = {
      .x = dst_x,
      .y = dst_y,
      .width = spr_width * world.scale,
      .height = spr_height * world.scale,
  };
  // DrawRectangle(dst_x, dst_y, 2, 2, RED);
  DrawTexturePro(sheet.tex, src, dst, {}, 0.0, WHITE);
  // DrawTexturePro(sheet.tex, src, dst, {}, 10.0, WHITE);
}


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SheetPool &pool) {
  auto view = world.reg.view<DrawPos>();
  for (auto [entity, draw_pos] : view.each()) {

    float dst_x = draw_pos.x * world.tile_size * world.scale;
    float dst_y = draw_pos.y * world.tile_size * world.scale;

    Sprite *sprite = impl::get_sprite_or_fallback(world, entity, dst_x, dst_y);
    if (!sprite)
      continue;

    Sheet *sheet =
        impl::get_sheet_or_fallback(world, pool, *sprite, dst_x, dst_y);
    if (!sheet)
      continue;

    impl::draw_sprite_texture(world, *sheet, *sprite, dst_x, dst_y);
  }
}


void yumeami::draw_world(World &world, SheetPool &pool) {
  draw_sprites(world, pool);
}
