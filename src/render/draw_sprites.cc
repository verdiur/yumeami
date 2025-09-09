#include "render/draw_sprites.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "logic/components.hh"
#include "raylib.h"


// NOTE: as of now camera wrapping is broken on worlds smaller than the
// viewport.


/* IMPL ***********************************************************************/


yumeami::Sprite *yumeami::impl::get_sprite(World &world, entt::entity ent,
                                           float dst_x, float dst_y) {
  Sprite *sprite = world.reg.try_get<Sprite>(ent);
  return sprite;
}


yumeami::Sheet *yumeami::impl::get_sheet(World &world, SheetPool &pool,
                                         const Sprite *sprite, float dst_x,
                                         float dst_y) {
  if (!sprite)
    return nullptr;
  Sheet *sheet = pool.get(sprite->sheet_id);
  return sheet;
}


// sprite drawing functions


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
  DrawTexturePro(sheet.tex, src, dst, {}, 0, WHITE);
}


void yumeami::impl::draw_fallback_no_sprite(World &world, float dst_x,
                                            float dst_y) {
  DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                world.tile_size * world.scale, BLUE);
  DrawText("no\nsprite", dst_x, dst_y, 1, WHITE);
}


void yumeami::impl::draw_fallback_no_sheet(World &world, float dst_x,
                                           float dst_y) {
  DrawRectangle(dst_x, dst_y, world.tile_size * world.scale,
                world.tile_size * world.scale, MAGENTA);
  DrawText("no\nsheet", dst_x, dst_y, 1, WHITE);
}


// draw management


bool yumeami::impl::is_sprite_off_camera(const World &world,
                                         const SafeRenderTex &vp,
                                         const Sheet *sheet, float dst_x,
                                         float dst_y) {
  CameraBounds bounds = get_camera_bounds(world, vp);
  if (dst_x < bounds.left || dst_y < bounds.top) {
    return true;
  }

  // fallback to tile size if sheet not found
  spx spr_width = (sheet) ? sheet->spr_width : world.tile_size;
  spx spr_height = (sheet) ? sheet->spr_height : world.tile_size;

  if (dst_x + spr_width * world.scale > bounds.right ||
      dst_y + spr_height * world.scale > bounds.bottom) {
    return true;
  }

  return false;
}


void yumeami::impl::draw_sprite(World &world, const Sheet *sheet,
                                const Sprite *sprite, float dst_x,
                                float dst_y) {
  if (!sprite)
    draw_fallback_no_sprite(world, dst_x, dst_y);
  else if (!sheet)
    draw_fallback_no_sheet(world, dst_x, dst_y);
  else
    draw_sprite_texture(world, *sheet, *sprite, dst_x, dst_y);
}


void yumeami::impl::draw_sprite_wrap(World &world, const Sheet *sheet,
                                     const Sprite *sprite, float dst_x,
                                     float dst_y, bool wrap_off_camera) {
  draw_sprite(world, sheet, sprite, dst_x, dst_y);
  if (wrap_off_camera) {
    float w = world.width * world.tile_size * world.scale;
    float h = world.height * world.tile_size * world.scale;

    // TODO: improve this i beg of you please. this is not smart, like, at all.
    draw_sprite(world, sheet, sprite, dst_x + w, dst_y);
    draw_sprite(world, sheet, sprite, dst_x - w, dst_y);
    draw_sprite(world, sheet, sprite, dst_x, dst_y + h);
    draw_sprite(world, sheet, sprite, dst_x, dst_y - h);

    draw_sprite(world, sheet, sprite, dst_x + w, dst_y + h);
    draw_sprite(world, sheet, sprite, dst_x - w, dst_y - h);
    draw_sprite(world, sheet, sprite, dst_x + w, dst_y - h);
    draw_sprite(world, sheet, sprite, dst_x - w, dst_y + h);
  }
}


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SafeRenderTex &vp, SheetPool &pool) {
  auto view = world.reg.view<DrawPos>();
  for (auto [entity, draw_pos] : view.each()) {

    float dst_x = draw_pos.x * world.tile_size * world.scale;
    float dst_y = draw_pos.y * world.tile_size * world.scale;

    Sprite *sprite = impl::get_sprite(world, entity, dst_x, dst_y);
    Sheet *sheet = impl::get_sheet(world, pool, sprite, dst_x, dst_y);

    bool is_off_camera =
        impl::is_sprite_off_camera(world, vp, sheet, dst_x, dst_y);
    impl::draw_sprite_wrap(world, sheet, sprite, dst_x, dst_y, is_off_camera);
  }
}
