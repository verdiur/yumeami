/**
 * @file main.cc
 * @brief Entry point
 */

#include "common/viewport_transform.hh"
#include "dbg/debug.hh"
#include "game/draw.hh"
#include "game/input.hh"
#include "game/movement.hh"
#include "game/world.hh"
#include "io/config_io.hh"
#include "raylib.h"


int main(int argc, char *argv[]) {

  /* SETUP ******************************************************************************/

  // init context
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640, 480, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory()); // app directory
  SetExitKey(KEY_ESCAPE);

  // load config
  std::optional<yumeami::ConfigSpec> cfg = yumeami::parse_config("res/config.json");
  if (!cfg) {
    return 1;
  }
  yumeami::load_config(cfg.value());

  // setup viewport
  RenderTexture viewport =
      LoadRenderTexture(cfg->viewport_width.get(), cfg->viewport_height.get());
  yumeami::ViewportTransform viewport_transform = {};
  yumeami::calc_viewport_scaling(viewport, viewport_transform);

  // INFO: debug world
  std::optional<yumeami::World> world_opt = yumeami::debug::load_test_world();
  if (!world_opt) {
    return 1;
  }
  yumeami::World &world = world_opt.value();
  yumeami::setup_camera(world, viewport);

  // events
  entt::dispatcher dispatcher = {};
  yumeami::setup_dispatcher_movement(dispatcher);

  /* GAME LOOP **************************************************************************/

  while (!WindowShouldClose()) {

    /* INPUT ****************************************************************************/

    yumeami::input(world, dispatcher);

    /* AI *******************************************************************************/

    /* UPDATE ***************************************************************************/

    yumeami::update_movement(world);

    /* DRAW: VIEWPORT MODE **************************************************************/

    BeginTextureMode(viewport);

    ClearBackground(BLACK);
    yumeami::draw_world(world, viewport);

    EndTextureMode();

    /* DRAW: WINDOW MODE ****************************************************************/

    BeginDrawing();

    ClearBackground(RED);
    yumeami::draw_viewport(viewport, viewport_transform);
    DrawFPS(10, 10);

    EndDrawing();
  }

  /* DE-INIT ****************************************************************************/

  yumeami::unload_world_textures(world);

  // unload raylib context
  UnloadRenderTexture(viewport);
  CloseAudioDevice();
  CloseWindow();
}
