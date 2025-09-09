#include "render/draw_world.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "raylib.h"
#include "render/draw_sprites.hh"
#include "resman/texture.hh"


void yumeami::draw_world(World &world, SheetPool &pool, SafeRenderTex &vp) {
  update_camera(world, vp, world.clamp_camera);

  BeginMode2D(world.cam);
  draw_sprites(world, vp, pool);
  EndMode2D();
}
