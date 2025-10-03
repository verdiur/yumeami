#include "render/draw_world.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "raylib.h"
#include "render/draw_background.hh"
#include "render/draw_sprites.hh"


void yumeami::draw_world(World &world, SheetCache &sheet_cache,
                         TextureCache &tex_cache, SafeRenderTex &vp) {
  update_camera(world, vp, world.config.clamp_camera);

  BeginMode2D(world.state.cam);
  draw_background(world, vp, tex_cache);
  draw_sprites(world, vp, sheet_cache);
  EndMode2D();
}
