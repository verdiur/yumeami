#include "render/draw.hh"
#include "assetmgr/texture.hh"
#include "logic/components.hh"
#include "raylib.h"
#include <memory>
#include <optional>


/* IMPL ***********************************************************************/


std::optional<yumeami::Sprite>
yumeami::impl::get_sprite_or_fallback(World &world, entt::entity ent,
                                      float dst_x, float dst_y) {
  auto sprite = world.reg.try_get<Sprite>(ent);
  if (!sprite) {
    DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                  world.tile_size * world.scale, BLUE);
    DrawText("no\nsprite", dst_x, dst_y, 1, WHITE);
  }
  return *sprite;
}


std::optional<std::shared_ptr<yumeami::Sheet>>
yumeami::impl::get_sheet_or_fallback(World &world, const SheetPool &pool,
                                     const Sprite &sprite, float dst_x,
                                     float dst_y) {
  auto sheet_opt = pool.get_sheet(sprite.sheet_id);
  if (!sheet_opt) {
    DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                  world.tile_size * world.scale, MAGENTA);
    DrawText("no\nsheet", dst_x, dst_y, 1, WHITE);
  }
  return sheet_opt;
}


void yumeami::impl::draw_sprite_texture(
    World &world, const std::optional<std::shared_ptr<Sheet>> opt_sheet_ptr,
    const std::optional<Sprite> opt_sprite, float dst_x, float dst_y) {
  spx spr_width = opt_sheet_ptr.value()->spr_width;
  spx spr_height = opt_sheet_ptr.value()->spr_height;

  Rectangle src = {
      .x = opt_sprite->col * spr_width,
      .y = opt_sprite->col * spr_height,
      .width = spr_width,
      .height = spr_height,
  };
  Rectangle dst = {
      .x = dst_x,
      .y = dst_y,
      .width = spr_width * world.scale,
      .height = spr_height * world.scale,
  };
  DrawTexturePro(opt_sheet_ptr.value()->tex, src, dst, {}, 0.0, WHITE);
}


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SheetPool &pool) {
  auto view = world.reg.view<DrawPos>();
  for (auto [entity, draw_pos] : view.each()) {

    float dst_x = draw_pos.x * world.tile_size * world.scale;
    float dst_y = draw_pos.y * world.tile_size * world.scale;

    auto opt_sprite = impl::get_sprite_or_fallback(world, entity, dst_x, dst_y);
    if (!opt_sprite)
      continue;

    auto opt_sheet_ptr =
        impl::get_sheet_or_fallback(world, pool, *opt_sprite, dst_x, dst_y);
    if (!opt_sheet_ptr)
      continue;

    impl::draw_sprite_texture(world, opt_sheet_ptr, opt_sprite, dst_x, dst_y);
  }
}


void yumeami::draw_world(World &world, SheetPool &pool) {
  draw_sprites(world, pool);
}
