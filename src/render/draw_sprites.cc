#include "render/draw_sprites.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "resman/spritesheet.hh"


/* IMPL ***********************************************************************/


void yumeami::impl::sort_sprites_zorder(WorldState &wstate) {
  wstate.reg.sort<ZOrder>([](const ZOrder &rhs, const ZOrder &lhs) {
    if (*rhs.floor != *lhs.floor)
      return *rhs.floor < *lhs.floor;

    if (rhs.elevation->elevation != lhs.elevation->elevation)
      return (int)rhs.elevation->elevation < (int)lhs.elevation->elevation;

    return (float)rhs.draw_pos->y < (float)lhs.draw_pos->y;
  });
}


yumeami::impl::SpriteAndSheet
yumeami::impl::get_sprite_and_sheet(WorldState &wstate, SheetCache &cache,
                                    entt::entity entity) {
  Sprite *sprite = wstate.reg.try_get<Sprite>(entity);
  Sheet *sheet = (sprite) ? cache.get(sprite->sheet_id) : nullptr;

  return SpriteAndSheet{sprite, sheet};
}


void yumeami::impl::draw_one_sprite(const WorldConfig &wconfig,
                                    const SpriteAndSheet &res,
                                    const DrawSpriteDst &dst, float scale) {
  if (!res.sprite) {
    DrawRectangle(dst.x, dst.y, scale, scale, BLUE);
    DrawText("no\nsprite", dst.x, dst.y, 1, WHITE);
    return;
  }

  if (!res.sheet) {
    DrawRectangle(dst.x, dst.y, scale, scale, MAGENTA);
    DrawText("no\nsheet", dst.x, dst.y, 1, WHITE);
    return;
  }

  spx spr_width = res.sheet->spr_width;
  spx spr_height = res.sheet->spr_height;

  Rectangle src_rec = {
      .x = res.sprite->col * spr_width,
      .y = res.sprite->row * spr_height,
      .width = spr_width,
      .height = spr_height,
  };

  // sprites are centered on the x axis and bottom-aligned on the y axis.
  float y_off = wconfig.scale * (spr_height - wconfig.tile_size);
  float x_off = wconfig.scale * ((spr_width - wconfig.tile_size) / 2);

  Rectangle dst_rec = {
      .x = dst.x - x_off,
      .y = dst.y - y_off,
      .width = spr_width * wconfig.scale,
      .height = spr_height * wconfig.scale,
  };

  DrawTexturePro(res.sheet->tex, src_rec, dst_rec, {}, 0, WHITE);
}


bool yumeami::impl::is_sprite_offcam(const WorldConfig &wconfig,
                                     const WorldState &wstate,
                                     const SafeRenderTex &vp,
                                     const SpriteAndSheet &res,
                                     const DrawSpriteDst &dst) {
  CameraBounds bounds = get_camera_bounds(wstate, vp);

  if (dst.x < bounds.left || dst.y < bounds.top) {
    return true;
  }

  spx spr_width = (res.sheet) ? res.sheet->spr_width : wconfig.tile_size;
  spx spr_height = (res.sheet) ? res.sheet->spr_height : wconfig.tile_size;

  if (dst.x + spr_width * wconfig.scale > bounds.right ||
      dst.y + spr_height * wconfig.scale > bounds.bottom) {
    return true;
  }

  return false;
}


void yumeami::impl::draw_one_sprite_wrap(const WorldConfig &wconfig,
                                         const SpriteAndSheet &res,
                                         const DrawSpriteDst &dst, float scale,
                                         bool wrap) {
  // NOTE: very, very naive implementation
  draw_one_sprite(wconfig, res, dst, scale);

  if (wrap) {
    float wwidth = wconfig.width * scale;
    float wheight = wconfig.height * scale;

    draw_one_sprite(wconfig, res, {dst.x + wwidth, dst.y}, scale);
    draw_one_sprite(wconfig, res, {dst.x - wwidth, dst.y}, scale);
    draw_one_sprite(wconfig, res, {dst.x, dst.y + wheight}, scale);
    draw_one_sprite(wconfig, res, {dst.x, dst.y - wheight}, scale);

    draw_one_sprite(wconfig, res, {dst.x + wwidth, dst.y + wheight}, scale);
    draw_one_sprite(wconfig, res, {dst.x - wwidth, dst.y + wheight}, scale);
    draw_one_sprite(wconfig, res, {dst.x + wwidth, dst.y - wheight}, scale);
    draw_one_sprite(wconfig, res, {dst.x - wwidth, dst.y - wheight}, scale);
  }
}


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SafeRenderTex &vp, SheetCache &cache) {
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;
  float scale = wconfig.tile_size * wconfig.scale;

  impl::sort_sprites_zorder(wstate);
  auto view = wstate.reg.view<ZOrder, DrawPos>();
  for (auto [ent, zorder, draw_pos] : view.each()) {

    const impl::DrawSpriteDst dst{
        .x = draw_pos.x * scale,
        .y = draw_pos.y * scale,
    };

    const impl::SpriteAndSheet res =
        impl::get_sprite_and_sheet(wstate, cache, ent);

    bool is_offcam = impl::is_sprite_offcam(wconfig, wstate, vp, res, dst);
    impl::draw_one_sprite_wrap(wconfig, res, dst, scale, is_offcam);
  }
}
