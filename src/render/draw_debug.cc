#include "render/draw_debug.hh"
#include "raylib.h"
#include <string>


void yumeami::draw_debug_info(int text_size) {
  int fps = GetFPS();
  DrawText((std::to_string(fps) + " FPS").c_str(), 3, 3, text_size, BLACK);
  DrawText((std::to_string(fps) + " FPS").c_str(), 2, 2, text_size, GREEN);
}
