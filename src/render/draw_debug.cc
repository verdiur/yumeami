#include "render/draw_debug.hh"
#include "common/direction.hh"
#include "logic/components.hh"
#include "raylib.h"
#include <string>


// DEBUG LINE COLORS
// WHITE: hitboxes
// GREEN: facing, entity component properties
// DARKBROWN: something invalid
// DARKGRAY: guides, like bounds or viewport center, etc.

// DEBUG TEXT COLORS
// GREEN/BLACK: fps

void yumeami::draw_debug_info(int text_size) {
  int fps = GetFPS();
  DrawText((std::to_string(fps) + " FPS").c_str(), 3, 3, text_size, BLACK);
  DrawText((std::to_string(fps) + " FPS").c_str(), 2, 2, text_size, GREEN);
}


void yumeami::draw_debug_collision(const World &world) {
  // NOTE: theres probably a way to optimize this
  BeginMode2D(world.cam);
  for (int x = 0; x < world.collision.get_width(); x++) {
    for (int y = 0; y < world.collision.get_height(); y++) {
      int val = world.collision.at(x, y);

      if (val > 0) {
        DrawRectangleLines(x * world.tile_size * world.scale,
                           y * world.tile_size * world.scale,
                           world.tile_size * world.scale,
                           world.tile_size * world.scale, WHITE);
        if (val > 1) {
          DrawText(std::to_string(val).c_str(),
                   x * world.tile_size * world.scale + 3,
                   y * world.tile_size * world.scale + 3, 1, BLACK);
          DrawText(std::to_string(val).c_str(),
                   x * world.tile_size * world.scale + 2,
                   y * world.tile_size * world.scale + 2, 1, WHITE);
        }
      }

      if (val < 0) {
        DrawRectangleLines(x * world.tile_size * world.scale,
                           y * world.tile_size * world.scale,
                           world.tile_size * world.scale,
                           world.tile_size * world.scale, MAROON);
        DrawText(std::to_string(val).c_str(),
                 x * world.tile_size * world.scale + 3,
                 y * world.tile_size * world.scale + 3, 1, BLACK);
        DrawText(std::to_string(val).c_str(),
                 x * world.tile_size * world.scale + 2,
                 y * world.tile_size * world.scale + 2, 1, MAROON);
      }
    }
  }
  EndMode2D();
}


void yumeami::draw_debug_world_bounds(const World &world) {
  BeginMode2D(world.cam);
  DrawRectangleLines(0, 0, world.width * world.tile_size * world.scale,
                     world.height * world.tile_size * world.scale, DARKGRAY);
  EndMode2D();
}


void yumeami::draw_debug_facing(const World &world, float arrow_length) {
  BeginMode2D(world.cam);
  auto view = world.reg.view<Facing, DrawPos>();
  for (auto [ent, fac, draw_pos] : view.each()) {

    Vector2 start_pos{
        .x = (draw_pos.x + 0.5f) * world.tile_size * world.scale,
        .y = (draw_pos.y + 0.5f) * world.tile_size * world.scale,
    };

    Vector2 end_pos{};
    switch (fac) {
    case Direction::UP:
      end_pos = {.x = start_pos.x, .y = start_pos.y - arrow_length};
    case Direction::DOWN:
      end_pos = {.x = start_pos.x, .y = start_pos.y + arrow_length};
    case Direction::LEFT:
      end_pos = {.x = start_pos.x - arrow_length, .y = start_pos.y};
    case Direction::RIGHT:
      end_pos = {.x = start_pos.x + arrow_length, .y = start_pos.y};
    }

    DrawLineV(start_pos, end_pos, GREEN);
  }
  EndMode2D();
}
