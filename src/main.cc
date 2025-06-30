#include "raylib.h"
#include "utils/display_manager.hh"

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

  // create virtual render target
  RenderTexture virtual_target = LoadRenderTexture(virtual_width, virtual_height);

  // create display manager
  yumeami::graphics::DisplayManager display_manager = { virtual_target };

  // game loop
  while (!WindowShouldClose()) {
    ClearBackground(BLACK);

    // render world on virtual target...

    // render game on window
    BeginTextureMode(virtual_target);
    ClearBackground(BLACK);
    EndTextureMode();

    yumeami::graphics::draw_virtual_target(display_manager);

    // debug info
    BeginDrawing();
    DrawFPS(10, 10);
    EndDrawing();
  }

  // de-initialization
  CloseWindow();

  return 0;
}
