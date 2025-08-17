/**
 * @file main.cc
 * @brief Entry point
 */

#include "common/viewport_transform.hh"
#include "entt/signal/fwd.hpp"
#include "game/debug.hh"
#include "game/draw.hh"
#include "game/input.hh"
#include "game/movement.hh"
#include "game/world.hh"
#include "io/config_io.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {

  /* SETUP ******************************************************************************/

  auto cfg = yumeami::parse_config(LoadFileText("assets/config.json"));
  if (!cfg) {
    spdlog::critical("configuration file not found");
    return 1;
  }

  // setup window
  InitWindow(cfg->window_width, cfg->window_height, "yumeami");
  SetExitKey(KEY_ESCAPE);
  if (cfg->vsync) {
    SetWindowState(FLAG_VSYNC_HINT);
  }

  // application directory
  ChangeDirectory(GetApplicationDirectory());

  // setup viewport
  RenderTexture viewport = LoadRenderTexture(cfg->viewport_width, cfg->viewport_height);
  yumeami::ViewportTransform viewport_transform = {};
  yumeami::calc_viewport_scaling(viewport, viewport_transform);

  // INFO: debug world
  yumeami::World world = yumeami::debug::create_collision_test_world();
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
  UnloadRenderTexture(viewport);
  CloseWindow();
}
