#include "render/draw_debug.hh"
#include "raylib.h"
#include <string>


void yumeami::draw_debug_info(int text_size) {
  int fps = GetFPS();
  DrawText((std::to_string(fps) + " FPS").c_str(), 3, 3, text_size, BLACK);
  DrawText((std::to_string(fps) + " FPS").c_str(), 2, 2, text_size, GREEN);
}


void yumeami::draw_debug_collision(const World &world) {
  // NOTE: theres probably a way to optimize this
  for (int x = 0; x < world.collision.get_width(); x++) {
    for (int y = 0; y < world.collision.get_height(); y++) {
      int val = world.collision.at(x, y);
      if (val > 0) {
        DrawRectangleLines(x, y, world.tile_size * world.scale,
                           world.tile_size * world.scale, WHITE);
        if (val > 1) {
          DrawText(std::to_string(val).c_str(), x + 2, y + 2, 1, WHITE);
        }
      }
    }
  }
}
