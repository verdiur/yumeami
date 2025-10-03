#include "render/draw_background.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "render/base.hh"
#include "resman/texture.hh"


void yumeami::draw_background(World &world, SafeRenderTex &vp,
                              TextureCache &cache) {
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;
  CameraBounds bounds = get_camera_bounds(wstate, vp);

  auto view = wstate.reg.view<Background, SpritePixelPos>();
  for (auto [ent, bg, pos] : view.each()) {

    SafeTexture *tex = cache.get(bg.texture_id);
    if (!tex) {
      DrawText("no spritesheet for bg", 0, 0, 30, DARKBROWN);
      continue;
    }

    Rectangle src{
        .x = 0,
        .y = 0,
        .width = (float)(*tex)->width,
        .height = (float)(*tex)->height,
    };
    Rectangle dst{
        // TODO: fix this jumping weirdly when wrapping
        .x = wstate.cam.target.x * bg.parallax + pos.x * wconfig.scale,
        .y = wstate.cam.target.y * bg.parallax + pos.y * wconfig.scale,
        .width = src.width * wconfig.scale,
        .height = src.height * wconfig.scale,
    };
    Vector2 spacing{
        .x = dst.width + bg.margin_x,
        .y = dst.height + bg.margin_y,
    };

    draw_texture_tiled(bounds, spacing, *tex, src, dst, {0, 0}, 0, WHITE);
  }
}
