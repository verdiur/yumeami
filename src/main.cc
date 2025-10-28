#include "common/viewport/viewport.hh"
#include "raylib.h"
#include "render/viewport.hh"
#include <entt/signal/dispatcher.hpp>

int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640, 480, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  entt::dispatcher dispatcher{};
  yumeami::Viewport vp(320, 240);
  yumeami::update_viewport_texel_scale(vp, dispatcher);

  while (!WindowShouldClose()) {
    BeginTextureMode(vp.rt);
    ClearBackground(BLACK);
    DrawLine(0, 0, 230, 230, WHITE);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(RED);
    yumeami::draw_viewport(vp);
    EndDrawing();
  }

  return 0;
}
