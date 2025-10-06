#include "_sandbox/decl.hh"
#include "ai/base.hh"
#include "ai/death.hh"
#include "common/raii.hh"
#include "common/viewport_transform.hh"
#include "entt/entt.hpp"
#include "input/input.hh"
#include "logic/animation.hh"
#include "logic/camera.hh"
#include "logic/collision.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "render/draw_debug.hh"
#include "render/draw_world.hh"
#include "resman/spritesheet.hh"
#include "resman/texture.hh"


int main(int argc, char *argv[]) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 * 2, 480 * 2, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  // SetWindowState(FLAG_VSYNC_HINT);
  SetTargetFPS(480);
  SetExitKey(KEY_ESCAPE);

  yumeami::SafeRenderTex vp(640 * 2, 480 * 2);
  yumeami::ViewportTransform vp_transform{};
  yumeami::calc_viewport_transform(vp, vp_transform);

  yumeami::SpritesheetCache sheet_cache{};
  yumeami::TextureCache tex_cache{};
  yumeami::World world =
      yumeami::sandbox::create_background_world(sheet_cache, tex_cache);
  yumeami::setup_camera(world, vp);

  entt::dispatcher dispatcher{};
  yumeami::setup_dispatcher_movement(dispatcher);
  yumeami::setup_dispatcher_collision(dispatcher);
  yumeami::setup_dispatcher_action(dispatcher);
  yumeami::setup_dispatcher_death(dispatcher);
  yumeami::setup_dispatcher_animation(dispatcher);

  while (!WindowShouldClose()) {

    // input + AI
    yumeami::update_input(world, dispatcher);
    yumeami::update_actions(world, dispatcher);

    // events
    dispatcher.update<yumeami::MovementEvent>();

    // state updates
    yumeami::update_movement_state(world, dispatcher);
    yumeami::update_animation_state(world, dispatcher);

    // draw on viewport
    BeginTextureMode(vp);
    ClearBackground(BLACK);
    yumeami::draw_debug_world_bounds(world);
    yumeami::draw_world(world, sheet_cache, tex_cache, vp);
    yumeami::draw_debug_facing(world, 50);
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
