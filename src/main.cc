#include "raylib.h"

int main(void) {

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(640 * 2, 480 * 2, "yumeami");
  InitAudioDevice();
  ChangeDirectory(GetApplicationDirectory());
  SetWindowState(FLAG_VSYNC_HINT);
  SetExitKey(KEY_ESCAPE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    EndDrawing();
  }

  return 0;
}
