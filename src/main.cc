#include "_sandbox/world.hh"
#include "ai/base.hh"
#include "ai/death.hh"
#include "common/raii.hh"
#include "common/viewport_transform.hh"
#include "entt/entt.hpp"
#include "input/input.hh"
#include "logic/camera.hh"
#include "logic/collision.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "render/draw_debug.hh"
#include "render/draw_world.hh"
#include "resman/spritesheet.hh"

int main(int argc, char *argv[]) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 * 2, 480 * 2, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  yumeami::SafeRenderTex vp(640, 480);
  yumeami::ViewportTransform vp_transform{};
  yumeami::calc_viewport_transform(vp, vp_transform);

  yumeami::SpritesheetCache spritesheet_cache{};
  yumeami::World world = yumeami::sandbox::create_random_move_world();
  yumeami::setup_camera(world, vp);

  entt::dispatcher dispatcher{};
  yumeami::setup_movement_event_dispatcher(dispatcher);
  yumeami::setup_update_collision_event_dispatcher(dispatcher);
  yumeami::setup_action_finished_event_dispatcher(dispatcher);
  yumeami::setup_death_event_dispatcher(dispatcher);

  while (!WindowShouldClose()) {

    // input + AI
    yumeami::update_input(world, dispatcher);
    yumeami::update_actions(world, dispatcher);

    // events
    dispatcher.update<yumeami::MovementEvent>();

    // state updates
    yumeami::update_movement_state(world, dispatcher);

    // draw on viewport
    BeginTextureMode(vp);
    ClearBackground(BLACK);
    yumeami::draw_world(world, spritesheet_cache, vp);
    EndTextureMode();

    // draw on window
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
