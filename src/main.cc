/**
 * @file main.cc
 * @brief Entry point
 */

#include "entt/signal/fwd.hpp"
#include "game/debug.hh"
#include "game/draw.hh"
#include "game/filesystem.hh"
#include "game/input.hh"
#include "game/movement.hh"
#include "game/world.hh"
#include "raylib.h"
#include "util/viewport_transform.hh"
#include <filesystem>
#include <optional>

int main(int argc, char *argv[]) {

  /* SETUP ******************************************************************************/

  const std::optional<std::filesystem::path> exe_dir = yumeami::get_exe_dir();
  if (exe_dir == std::nullopt) {
    return 1;
  }

  // window dimensions
  const int window_width = 640 * 2;
  const int window_height = 480 * 2;

  // setup window
  InitWindow(window_width, window_height, "yumeami");
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  // setup viewport
  const int viewport_width = 640;
  const int viewport_height = 480;
  RenderTexture viewport = LoadRenderTexture(viewport_width, viewport_height);
  yumeami::ViewportTransform viewport_transform = {};
  yumeami::calc_viewport_scaling(viewport, viewport_transform);

  // INFO: debug world
  yumeami::World world = yumeami::debug::create_player_test_world();
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

  CloseWindow();
}
