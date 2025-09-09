#include "_sandbox/world.hh"
#include "common/raii.hh"
#include "common/viewport_transform.hh"
#include "entt/entt.hpp"
#include "input/input.hh"
#include "logic/camera.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "render/draw_debug.hh"
#include "render/draw_world.hh"
#include "resman/texture.hh"

int main(int argc, char *argv[]) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640, 480, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  // SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  yumeami::SafeRenderTex vp(640, 480);
  yumeami::ViewportTransform vp_transform{};
  yumeami::calc_viewport_transform(vp, vp_transform);

  yumeami::SheetPool sheet_pool{};
  yumeami::World world =
      yumeami::_sandbox::create_spritesheet_world(sheet_pool);
  yumeami::setup_camera(world, vp);
  // yumeami::World world = {
  //     .width = 20,
  //     .height = 15,
  //     .tile_size = 16,
  //     .wrap = false,
  //     .scale = 2,
  //     .reg = {},
  //     .sheet_ids = {},
  // };
  entt::dispatcher dispatcher{};
  yumeami::setup_movement_event_dispatcher(dispatcher);

  while (!WindowShouldClose()) {

    yumeami::update_input(world, dispatcher);
    yumeami::update_movement_state(world);

    BeginTextureMode(vp);
    ClearBackground(BLACK);
    yumeami::draw_world(world, sheet_pool, vp);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    yumeami::draw_viewport(vp, vp_transform);
    yumeami::draw_debug_info(10);
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
