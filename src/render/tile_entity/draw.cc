#include "render/tile_entity/draw.hh"
#include "common/types/vector.hh"
#include "model/camera/camera.hh"
#include "model/components/common.hh"
#include "model/components/sprite.hh"
#include "model/spritesheet/spritesheet.hh"
#include "model/viewport/viewport.hh"
#include "model/world/world.hh"
#include "render/core/color.hh"
#include "render/core/raylib_tx.hh"
#include "render/core/tiled.hh"
#include <entt/entity/fwd.hpp>
#include <raylib.h>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  /**
   * @brief Draw a single fallback tile
   */
  void draw_one_fallback(World &world, const Viewport &vp, TexelVector2 dst,
                         Color color, std::string msg) {
    Rectangle dst_rec{
        dst.x,
        dst.y,
        world.config.tile_size,
        world.config.tile_size,
    };
    draw_rectangle_tx(vp.tx_size, dst_rec, {}, 0, color);
    draw_text_tx_raw(vp.tx_size, msg, dst_rec.x, dst_rec.y, 1, WHITE);
  }


  /**
   * @brief Draw a single fallback tile, tiled across the camera for
   * wrapping.
   */
  void draw_one_fallback_tiled(World &world, const Viewport &vp,
                               const CameraBounds &bounds, TexelVector2 dst,
                               TexelVector2 spacing, Color color,
                               std::string msg) {
    draw_tiled_tx(bounds, spacing, dst, [&](TexelVector2 pos) {
      draw_one_fallback(world, vp, pos, color, msg);
    });
  }


  /**
   * @brief Draw a single entity
   * @param world world
   * @param vp viewport
   * @param bounds camera bounds
   * @param ent entity
   * @param dst destination in texels.
   */
  void draw_one_tile_entity(World &world, const Viewport &vp,
                            const CameraBounds &bounds, entt::entity ent,
                            TexelVector2 dst) {
    Sprite *sprite = world.state.registry.try_get<Sprite>(ent);
    TexelVector2 tile_spacing{tile_to_tx(world, world.config.width),
                              tile_to_tx(world, world.config.height)};

    // fallback: no sprite
    if (!sprite) {
      if (!world.config.wrap) {
        draw_one_fallback(world, vp, dst, COLOR_NO_SPRITE, "no sprite");
      } else {
        draw_one_fallback_tiled(world, vp, bounds, dst, tile_spacing,
                                COLOR_NO_SPRITE, "no_sprite");
      }
    }

    Spritesheet &sheet = sprite->spritesheet;
    SafeTexture &tex = sheet.texture;
    Rectangle src_rec = sheet.source_rec_at(sprite->row, sprite->col);

    // draw
    if (!world.config.wrap) {
      Rectangle dst_rec{
          dst.x,
          dst.y,
          sheet.sprite_width,
          sheet.sprite_height,
      };
      draw_texture_pro_tx(vp.tx_size, tex, src_rec, dst_rec, {}, 0, WHITE);

    } else {
      draw_tiled_tx(bounds, tile_spacing, dst, [&](TexelVector2 pos) {
        Rectangle dst_rec{
            pos.x,
            pos.y,
            sheet.sprite_width,
            sheet.sprite_height,
        };
        draw_texture_pro_tx(vp.tx_size, tex, src_rec, dst_rec, {}, 0, WHITE);
      });
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::draw_tile_entities(World &world, Viewport &vp) {
  CameraBounds bounds = CameraBounds::create(world, vp);

  auto view = world.state.registry.view<DrawTilePos>();
  for (auto [ent, draw_pos] : view.each()) {
    TexelVector2 dst{
        .x = tile_to_tx(world, draw_pos.pos.x),
        .y = tile_to_tx(world, draw_pos.pos.y),
    };
    draw_one_tile_entity(world, vp, bounds, ent, dst);
  }
}
