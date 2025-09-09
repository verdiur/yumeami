#include "render/draw_sprites.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "logic/components.hh"


/* IMPL ***********************************************************************/


yumeami::Sprite *yumeami::impl::get_sprite(World &world, entt::entity ent,
                                           float dst_x, float dst_y,
                                           DrawSpriteStatus &status) {
  Sprite *sprite = world.reg.try_get<Sprite>(ent);
  if (!sprite)
    status = DrawSpriteStatus::NO_SPRITE;
  else
    status = DrawSpriteStatus::OK;
  return sprite;
}


yumeami::Sheet *yumeami::impl::get_sheet(World &world, SheetPool &pool,
                                         const Sprite *sprite, float dst_x,
                                         float dst_y,
                                         DrawSpriteStatus &status) {
  if (!sprite)
    return nullptr;

  Sheet *sheet = pool.get(sprite->sheet_id);
  if (!sheet)
    status = DrawSpriteStatus::NO_SHEET;
  else
    status = DrawSpriteStatus::OK;
  return sheet;
}


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


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SafeRenderTex &vp, SheetPool &pool) {
  auto view = world.reg.view<DrawPos>();
  for (auto [entity, draw_pos] : view.each()) {
    DrawSpriteStatus status = DrawSpriteStatus::OK;

    float dst_x = draw_pos.x * world.tile_size * world.scale;
    float dst_y = draw_pos.y * world.tile_size * world.scale;

    Sprite *sprite = impl::get_sprite(world, entity, dst_x, dst_y, status);
    Sheet *sheet = impl::get_sheet(world, pool, sprite, dst_x, dst_y, status);

    switch (status) {
    case DrawSpriteStatus::OK:
      impl::draw_sprite_texture(world, *sheet, *sprite, dst_x, dst_y);
      break;

    case DrawSpriteStatus::NO_SPRITE:
      impl::draw_fallback_no_sprite(world, dst_x, dst_y);
      break;

    case DrawSpriteStatus::NO_SHEET:
      impl::draw_fallback_no_sheet(world, dst_x, dst_y);
      break;
    }
  }
}
