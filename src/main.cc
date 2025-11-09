#include "model/viewport/viewport.hh"
#include "render/viewport/draw.hh"
#include "resources/resources.hh"
#include <entt/signal/dispatcher.hpp>
#include <entt/signal/fwd.hpp>
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

  entt::dispatcher dispatcher{};
  yumeami::ResourceCaches pools{};
  yumeami::Viewport vp(320, 240, yumeami::calc_best_tx_size(320, 240),
                       pools.render_texture_pool);

  while (!WindowShouldClose()) {
    yumeami::begin_viewport_texture_mode(vp);
    ClearBackground(BLACK);
    yumeami::end_viewport_texture_mode();

    BeginDrawing();
    ClearBackground(GRAY);
    yumeami::draw_viewport(vp);
    EndDrawing();

    if (IsWindowResized()) {
      vp.update_viewport_size(pools.render_texture_pool, dispatcher);
    }
  }

  return 0;
}
