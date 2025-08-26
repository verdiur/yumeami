#include "common/viewport_transform.hh"
#include "graphics/texture.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "renderer/draw.hh"

int main(int argc, char *argv[]) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640, 480, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  RenderTexture vp = LoadRenderTexture(640, 480);
  yumeami::ViewportTransform vp_transform{};
  yumeami::calc_viewport_transform(vp, vp_transform);

  yumeami::World world{
      .width = 20, .height = 15, .tile_size = 16, .scale = 2, .wrap = false};
  yumeami::SheetPool sheet_pool{};

  while (!WindowShouldClose()) {

    BeginTextureMode(vp);
    yumeami::draw_world(world, sheet_pool);
    EndTextureMode();

    BeginDrawing();
    yumeami::draw_viewport(vp, vp_transform);
    EndDrawing();
  }

  UnloadRenderTexture(vp);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
