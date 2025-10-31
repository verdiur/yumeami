#include "model/viewport.hh"
#include "resources/render_texture_cache.hh"
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>


int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 + 40, 480 + 40, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  // caches
  yumeami::SafeRenderTextureCache rt_cache{};

  // dispatcher
  entt::dispatcher dispatcher{};

  yumeami::Viewport vp(640, 480, 2, rt_cache);

  while (!WindowShouldClose()) {
    BeginTextureMode(*vp.rt.handle());
    ClearBackground(BLACK);
    EndTextureMode();

    BeginDrawing();
    // ClearBackground(RED);
    // yumeami::draw_viewport(vp);
    EndDrawing();
  }

  return 0;
}
