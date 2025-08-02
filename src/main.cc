/**
 * @file main.cc
 * @brief Entry point
 */

#include "raylib.h"
#include "util/viewport_transform.hh"

int main(int argc, char *argv[]) {

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

  // game loop
  while (!WindowShouldClose()) {

    /* DRAW: BEGIN VIEWPORT MODE ********************************************************/

    BeginTextureMode(viewport);
    ClearBackground(BLACK);
    EndTextureMode();

    /* DRAW: END VIEWPORT MODE **********************************************************/
    /* DRAW: BEGIN WINDOW MODE **********************************************************/

    BeginDrawing();

    ClearBackground(RED);
    yumeami::draw_viewport(viewport, viewport_transform);
    DrawFPS(10, 10);

    EndDrawing();

    /* DRAW: END WINDOW MODE ************************************************************/
  }

  CloseWindow();
}
