#include "entt/signal/fwd.hpp"
#include "game/event/input.hh"
#include "game/system/draw.hh"
#include "game/system/movement.hh"
#include "game/world.hh"
#include "raylib.h"
#include "util/display_manager.hh"

int
main(int argc, char* argv[])
{
  // real window dimensions
  const int window_width = 640 * 2;
  const int window_height = 480 * 2;

  // virtual window dimensions
  const int virtual_width = 640;
  const int virtual_height = 480;

  // create raylib window
  InitWindow(window_width, window_height, "yumenet");
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  // create virtual render target
  RenderTexture virtual_target = LoadRenderTexture(virtual_width, virtual_height);

  // create and setup display manager
  yumeami::DisplayManager display_manager = {};
  yumeami::setup_display_manager(virtual_target, display_manager);

  // TODO: placeholder
  // create world
  yumeami::World world = yumeami::create_dummy_world();

  // initialize input
  entt::dispatcher dispatcher{};
  yumeami::sys::setup_connect_move_events(dispatcher, world.registry);

  // game loop
  while (!WindowShouldClose()) {

    /* INPUT ****************************************************************************/

    yumeami::sys::dispatch_input_events(world.registry, dispatcher);

    /* UPDATE ***************************************************************************/

    yumeami::sys::update_movement(world.registry);

    /* DRAWING **************************************************************************/

    // render world on virtual target
    BeginTextureMode(virtual_target);
    yumeami::sys::draw_world(world);
    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);

    // render game on window
    yumeami::draw_virtual_target_on_window(virtual_target, display_manager);

    // debug info
    DrawFPS(10, 10);

    EndDrawing();

    /* END LOOP *************************************************************************/
  }

  // de-initialization
  CloseWindow();

  return 0;
}
