#include "common/viewport_transform.hh"
#include "raylib.h"

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

  while (!WindowShouldClose()) {
    BeginDrawing();
    yumeami::draw_viewport(vp, vp_transform);
    EndDrawing();
  }

  UnloadRenderTexture(vp);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
