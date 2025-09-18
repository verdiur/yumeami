#include "render/draw_debug.hh"
#include "common/direction.hh"
#include "logic/components.hh"
#include "logic/world.hh"
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
  const WorldConfig &wconfig = world.config;
  const WorldState &wstate = world.state;

  BeginMode2D(wstate.cam);
  for (int x = 0; x < wstate.collision.get_width(); x++) {
    for (int y = 0; y < wstate.collision.get_height(); y++) {
      int val = wstate.collision.at(x, y);

      if (val > 0) {
        DrawRectangleLines(x * wconfig.tile_size * wconfig.scale,
                           y * wconfig.tile_size * wconfig.scale,
                           wconfig.tile_size * wconfig.scale,
                           wconfig.tile_size * wconfig.scale, WHITE);
        if (val > 1) {
          DrawText(std::to_string(val).c_str(),
                   x * wconfig.tile_size * wconfig.scale + 3,
                   y * wconfig.tile_size * wconfig.scale + 3, 1, BLACK);
          DrawText(std::to_string(val).c_str(),
                   x * wconfig.tile_size * wconfig.scale + 2,
                   y * wconfig.tile_size * wconfig.scale + 2, 1, WHITE);
        }
      }

      if (val < 0) {
        DrawRectangleLines(x * wconfig.tile_size * wconfig.scale,
                           y * wconfig.tile_size * wconfig.scale,
                           wconfig.tile_size * wconfig.scale,
                           wconfig.tile_size * wconfig.scale, MAROON);
        DrawText(std::to_string(val).c_str(),
                 x * wconfig.tile_size * wconfig.scale + 3,
                 y * wconfig.tile_size * wconfig.scale + 3, 1, BLACK);
        DrawText(std::to_string(val).c_str(),
                 x * wconfig.tile_size * wconfig.scale + 2,
                 y * wconfig.tile_size * wconfig.scale + 2, 1, MAROON);
      }
    }
  }
  EndMode2D();
}


void yumeami::draw_debug_world_bounds(const World &world) {
  const WorldConfig &wconfig = world.config;
  BeginMode2D(world.state.cam);
  DrawRectangleLines(0, 0, wconfig.width * wconfig.tile_size * wconfig.scale,
                     wconfig.height * wconfig.tile_size * wconfig.scale,
                     DARKGRAY);
  EndMode2D();
}


void yumeami::draw_debug_facing(const World &world, float arrow_length) {
  const WorldConfig &wconfig = world.config;
  const WorldState &wstate = world.state;

  BeginMode2D(wstate.cam);
  auto view = wstate.reg.view<Facing, DrawPos>();
  for (auto [ent, fac, draw_pos] : view.each()) {

    Vector2 start_pos{
        .x = (draw_pos.x + 0.5f) * wconfig.tile_size * wconfig.scale,
        .y = (draw_pos.y + 0.5f) * wconfig.tile_size * wconfig.scale,
    };

    Vector2 end_pos{};
    switch (fac) {
    case Direction::UP:
      end_pos = {.x = start_pos.x, .y = start_pos.y - arrow_length};
      break;
    case Direction::DOWN:
      end_pos = {.x = start_pos.x, .y = start_pos.y + arrow_length};
      break;
    case Direction::LEFT:
      end_pos = {.x = start_pos.x - arrow_length, .y = start_pos.y};
      break;
    case Direction::RIGHT:
      end_pos = {.x = start_pos.x + arrow_length, .y = start_pos.y};
      break;
    }

    DrawLineV(start_pos, end_pos, GREEN);
  }
  EndMode2D();
}
