#include "model/viewport.hh"
#include "render/draw_viewport.hh"
#include "resources/render_texture_cache.hh"
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>


int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 * 2, 480 * 2, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  yumeami::SafeRenderTextureCache rt_cache{};
  yumeami::Viewport vp(320, 240, yumeami::calc_best_tx_scale(320, 240),
                       rt_cache);

  while (!WindowShouldClose()) {
    BeginTextureMode(vp.render_texture());
    ClearBackground(BLACK);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(GRAY);
    yumeami::draw_viewport(vp);
    EndDrawing();
  }

  return 0;
}
