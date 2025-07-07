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
  const int window_width = 640;
  const int window_height = 480;

  // virtual window dimensions
  const int virtual_width = 640;
  const int virtual_height = 480;

  // create raylib window
  InitWindow(window_width, window_height, "yumenet");
  // SetWindowState(FLAG_VSYNC_HINT);
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
  yumeami::sys::initialize_input_event_dispatcher(dispatcher, world.registry);

  // game loop
  while (!WindowShouldClose()) {
    // input
    yumeami::dispatch_input_events(dispatcher);

    // update
    yumeami::sys::update_movement(world.registry);

    BeginDrawing();
    ClearBackground(BLACK);

    // render world on virtual target
    yumeami::sys::draw_world(world, virtual_target);

    // render game on window
    yumeami::draw_virtual_target_on_window(virtual_target, display_manager);

    // debug info
    DrawFPS(10, 10);
    EndDrawing();
  }

  // de-initialization
  CloseWindow();

  return 0;
}
