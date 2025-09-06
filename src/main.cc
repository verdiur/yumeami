#include "assetmgr/texture.hh"
#include "common/viewport_transform.hh"
#include "entt/entt.hpp"
#include "input/input.hh"
#include "logic/movement.hh"
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

  yumeami::SheetPool sheet_pool{};
  yumeami::World world = yumeami::test::test_spritesheet_world(sheet_pool);
  entt::dispatcher dispatcher{};
  yumeami::setup_movement_event_dispatcher(dispatcher);

  while (!WindowShouldClose()) {

    yumeami::update_input(world, dispatcher);
    yumeami::update_movement_state(world);

    BeginTextureMode(vp);
    ClearBackground(BLACK);
    yumeami::draw_world(world, sheet_pool);
    DrawRectangle(0, 0, 4, 4, GREEN);
    DrawTexture(sheet_pool.get_sheet("test_spritesheet")->tex, 0, 0, WHITE);
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
