#include "render/base.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"


namespace {
  using namespace yumeami;


  void draw_texture_row(const CameraBounds &bounds, const Vector2 &spacing,
                        const SafeTex &texture, const Rectangle &src,
                        const Rectangle &dst, const Vector2 &origin,
                        const float rotation, const Color &tint) {
    float current_x_pos = dst.x;
    while (current_x_pos >= bounds.left) {
      current_x_pos -= spacing.x;
    }

    while (current_x_pos <= bounds.right) {
      Rectangle offset_x_dst = {
          .x = current_x_pos,
          .y = dst.y,
          .width = dst.width,
          .height = dst.height,
      };
      DrawTexturePro(texture, src, offset_x_dst, origin, rotation, tint);
      current_x_pos += spacing.x;
    }
  }


  void draw_fallback_row(const CameraBounds &bounds, const Vector2 &spacing,
                         const Rectangle &dst, const Color &tint,
                         const std::string msg) {
    float current_x_pos = dst.x;
    while (current_x_pos >= bounds.left) {
      current_x_pos -= spacing.x;
    }

    while (current_x_pos <= bounds.right) {
      Rectangle offset_x_dst = {
          .x = current_x_pos,
          .y = dst.y,
          .width = dst.width,
          .height = dst.height,
      };
      DrawRectangleRec(offset_x_dst, tint);
      DrawText(msg.c_str(), offset_x_dst.x, offset_x_dst.y, 1, WHITE);
      current_x_pos += spacing.x;
    }
  }


} // namespace


void yumeami::draw_texture_tiled(const CameraBounds &bounds,
                                 const Vector2 spacing, const SafeTex &texture,
                                 const Rectangle src, const Rectangle dst,
                                 const Vector2 origin, const float rotation,
                                 const Color tint) {
  float current_y_pos = dst.y;
  while (current_y_pos >= bounds.top) {
    current_y_pos -= spacing.y;
  }

  while (current_y_pos <= bounds.bottom) {
    Rectangle offset_y_dst = {
        .x = dst.x,
        .y = current_y_pos,
        .width = dst.width,
        .height = dst.height,
    };
    draw_texture_row(bounds, spacing, texture, src, offset_y_dst, origin,
                     rotation, tint);
    current_y_pos += spacing.y;
  };
}


void yumeami::draw_fallback_tiled(const CameraBounds &bounds,
                                  const Vector2 spacing, const Rectangle dst,
                                  const Color tint, const std::string msg) {
  float current_y_pos = dst.y;
  while (current_y_pos >= bounds.top) {
    current_y_pos -= spacing.y;
  }

  while (current_y_pos <= bounds.bottom) {
    Rectangle offset_y_dst = {
        .x = dst.x,
        .y = current_y_pos,
        .width = dst.width,
        .height = dst.height,
    };
    draw_fallback_row(bounds, spacing, offset_y_dst, tint, msg);
    current_y_pos += spacing.y;
  };
}
