#include "render/draw_sprites.hh"
#include "logic/camera.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include "raylib.h"
#include "render/base.hh"
#include <cmath>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  struct DstCoords {
    float x;
    float y;
  };


  struct Resources {
    const Sprite *sprite;
    const Sheet *sheet;
  };


  /**
   * @brief Sort sprites by z-order.
   * @param wstate
   */
  void sort_sprites(WorldState &wstate) {
    wstate.reg.sort<ZSort>(
        [](const ZSort &lhs, const ZSort &rhs) { return lhs < rhs; });
  }


  /**
   * @brief Get resources necessary to draw a sprite
   * @param wstate
   * @param cache
   * @param entity
   * @return
   */
  Resources get_resources(WorldState &wstate, SheetCache &cache,
                          entt::entity entity) {
    Sprite *sprite = wstate.reg.try_get<Sprite>(entity);
    Sheet *sheet = (sprite) ? cache.get(sprite->sheet_id) : nullptr;

    return Resources{sprite, sheet};
  }


  /**
   * @brief Draw a single sprite. Implements wrap drawing
   * @param wconfig
   * @param bounds
   * @param res
   * @param coords
   * @param scaled_tile_size
   */
  void draw_one_sprite(const WorldConfig &wconfig, const CameraBounds &bounds,
                       const Resources &res, DstCoords &coords,
                       float scaled_tile_size) {
    DstCoords floored_coords = {
        std::floorf(coords.x),
        std::floorf(coords.y),
    };

    Vector2 spacing = {
        .x = wconfig.width * scaled_tile_size,
        .y = wconfig.height * scaled_tile_size,
    };

    Rectangle fallback_dst = {
        .x = floored_coords.x,
        .y = floored_coords.y,
        .width = scaled_tile_size,
        .height = scaled_tile_size,
    };

    if (!res.sprite) {
      if (!wconfig.wrap) {
        draw_fallback(fallback_dst, COLOR_NO_SPRITE, "no\nsprite");
      } else {
        draw_fallback_tiled(bounds, spacing, fallback_dst, COLOR_NO_SPRITE,
                            "no\nsprite");
      }
      return;
    }

    if (!res.sheet) {
      if (!wconfig.wrap) {
        draw_fallback(fallback_dst, COLOR_NO_SPRITE, "no\nsprite");
      } else {
        draw_fallback_tiled(bounds, spacing, fallback_dst, COLOR_NO_SHEET,
                            "no\nsheet");
      }
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
        .x = floored_coords.x - x_off,
        .y = floored_coords.y - y_off,
        .width = spr_width * wconfig.scale,
        .height = spr_height * wconfig.scale,
    };

    if (!wconfig.wrap) {
      DrawTexturePro(res.sheet->tex, src_rec, dst_rec, {0, 0}, 0, WHITE);
    } else {
      draw_texture_tiled(bounds, spacing, res.sheet->tex, src_rec, dst_rec,
                         {0, 0}, 0, WHITE);
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::draw_sprites(World &world, SafeRenderTex &vp, SheetCache &cache) {
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;
  float scaled_tile_size = wconfig.tile_size * wconfig.scale;
  CameraBounds bounds = get_camera_bounds(wstate, vp);

  sort_sprites(wstate);
  auto view = wstate.reg.view<ZSort, DrawPos>();
  for (auto [ent, zsort, draw_pos] : view.each()) {

    DstCoords dst{
        .x = draw_pos.x * scaled_tile_size,
        .y = draw_pos.y * scaled_tile_size,
    };

    const Resources res = get_resources(wstate, cache, ent);
    draw_one_sprite(wconfig, bounds, res, dst, scaled_tile_size);
  }
}
