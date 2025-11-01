#include "model/viewport/viewport.hh"
#include "render/draw_viewport.hh"
#include "resources/render_texture_cache.hh"
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>
#include <spdlog/spdlog.h>


int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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

    if (IsWindowResized()) {
      vp.update_viewport_size(rt_cache);
    }
  }

  return 0;
}
