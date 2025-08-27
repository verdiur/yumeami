#include "assetmgt/texture.hh"
#include "common/viewport_transform.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "render/draw.hh"
#include "test/test_worlds.hh"

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

  yumeami::World world = yumeami::test::test_create_world();
  yumeami::SheetPool sheet_pool{};

  while (!WindowShouldClose()) {

    BeginTextureMode(vp);
    ClearBackground(BLACK);
    yumeami::draw_world(world, sheet_pool);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    yumeami::draw_viewport(vp, vp_transform);
    EndDrawing();
  }

  UnloadRenderTexture(vp);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
