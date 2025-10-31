// #include "common/viewport/viewport.hh"
#include "raylib.h"
// #include "render/viewport.hh"
#include <entt/signal/dispatcher.hpp>

int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 * 40, 480 * 40, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  entt::dispatcher dispatcher{};
  // yumeami::Viewport vp(320, 240, yumeami::calc_viewport_texel_scale(320,
  // 240));

  while (!WindowShouldClose()) {
    // BeginTextureMode(vp.rt);
    // ClearBackground(BLACK);
    // EndTextureMode();
    //
    // BeginDrawing();
    // ClearBackground(RED);
    // yumeami::draw_viewport(vp);
    // EndDrawing();
  }

  return 0;
}
