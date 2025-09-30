#include "render/draw_sprites.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include "raylib.h"
#include "resman/spritesheet.hh"
#include <cmath>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  struct DrawSpriteDst {
    float x;
    float y;
  };


  struct SpriteAndSheet {
    const Sprite *sprite;
    const Sheet *sheet;
  };


  void sort_sprites_zorder(WorldState &wstate) {
    wstate.reg.sort<ZSort>(
        [](const ZSort &lhs, const ZSort &rhs) { return lhs < rhs; });
  }


  SpriteAndSheet get_sprite_and_sheet(WorldState &wstate, SheetCache &cache,
                                      entt::entity entity) {
    Sprite *sprite = wstate.reg.try_get<Sprite>(entity);
    Sheet *sheet = (sprite) ? cache.get(sprite->sheet_id) : nullptr;

    return SpriteAndSheet{sprite, sheet};
  }


  /**
   * @brief Draw a single sprite. Fallback if resources are missing.
   */
  void draw_one_sprite(const WorldConfig &wconfig, const SpriteAndSheet &res,
                       const DrawSpriteDst &dst, float scale) {
    // we need to explicitly floor the coordinates, otherwise they are truncated
    // by raylib (causes the coords being offset by 1px when negative)
    float dst_x_floor = std::floorf(dst.x);
    float dst_y_floor = std::floorf(dst.y);

    if (!res.sprite) {
      DrawRectangle(dst_x_floor, dst_y_floor, scale, scale, BLUE);
      DrawText("no\nsprite", dst_x_floor, dst_y_floor, 1, WHITE);
      return;
    }

    if (!res.sheet) {
      DrawRectangle(dst_x_floor, dst_y_floor, scale, scale, MAGENTA);
      DrawText("no\nsheet", dst_x_floor, dst_y_floor, 1, WHITE);
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
        .x = dst_x_floor - x_off,
        .y = dst_y_floor - y_off,
        .width = spr_width * wconfig.scale,
        .height = spr_height * wconfig.scale,
    };

    DrawTexturePro(res.sheet->tex, src_rec, dst_rec, {}, 0, WHITE);
  }


  bool is_sprite_offcam(const WorldConfig &wconfig, const WorldState &wstate,
                        const SafeRenderTex &vp, const SpriteAndSheet &res,
                        const DrawSpriteDst &dst) {
    CameraBounds bounds = get_camera_bounds(wstate, vp);

    if (dst.x < bounds.left || dst.y < bounds.top)
      return true;

    spx spr_width = (res.sheet) ? res.sheet->spr_width : wconfig.tile_size;
    spx spr_height = (res.sheet) ? res.sheet->spr_height : wconfig.tile_size;

    if (dst.x + spr_width * wconfig.scale > bounds.right ||
        dst.y + spr_height * wconfig.scale > bounds.bottom)
      return true;

    return false;
  }


  /**
   * @brief Draw a single sprite, and draw it around the visible world
   * boundaries if wrap_off_camera is true. This ensures seamless wrapped world
   * drawing by filling in the empty space to create an illusion of an infinite
   * world.
   */
  void draw_one_sprite_wrap(const WorldConfig &wconfig,
                            const SpriteAndSheet &res, const DrawSpriteDst &dst,
                            float scale, bool wrap) {
    // NOTE: very, very naive implementation
    draw_one_sprite(wconfig, res, dst, scale);

    if (wrap) {
      float wwidth = wconfig.width * scale;   // window width
      float wheight = wconfig.height * scale; // window height

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


} // namespace


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SafeRenderTex &vp, SheetCache &cache) {
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;
  float scale = wconfig.tile_size * wconfig.scale;

  sort_sprites_zorder(wstate);
  auto view = wstate.reg.view<ZSort, DrawPos>();
  for (auto [ent, zsort, draw_pos] : view.each()) {

    const DrawSpriteDst dst{
        .x = draw_pos.x * scale,
        .y = draw_pos.y * scale,
    };

    const SpriteAndSheet res = get_sprite_and_sheet(wstate, cache, ent);
    bool is_offcam = is_sprite_offcam(wconfig, wstate, vp, res, dst);
    draw_one_sprite_wrap(wconfig, res, dst, scale, is_offcam);
  }
}
