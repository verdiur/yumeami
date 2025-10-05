#include "render/base.hh"
#include "common/raii.hh"
#include "logic/camera.hh"
#include "raylib.h"


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  void draw_texture_row(const CameraBounds &cam_bounds, const SafeTex &tex,
                        const Vector2 &spacing, const Rectangle &src,
                        const Rectangle &dst, const Vector2 &origin,
                        const float rotation, const Color &tint) {
    float current_x_pos = dst.x;
    while (current_x_pos >= cam_bounds.left) {
      current_x_pos -= spacing.x;
    }

    while (current_x_pos <= cam_bounds.right) {
      Rectangle offset_x_dst = {
          .x = current_x_pos,
          .y = dst.y,
          .width = dst.width,
          .height = dst.height,
      };
      DrawTexturePro(tex, src, offset_x_dst, origin, rotation, tint);
      current_x_pos += spacing.x;
    }
  }


  void draw_fallback_row(const CameraBounds &cam_bounds, const Vector2 &spacing,
                         const Rectangle &dst, const Color &tint,
                         const std::string msg) {
    float current_x_pos = dst.x;
    while (current_x_pos >= cam_bounds.left) {
      current_x_pos -= spacing.x;
    }

    while (current_x_pos <= cam_bounds.right) {
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


/* PUBL ***********************************************************************/


void yumeami::draw_fallback(const Rectangle dst, const Color tint,
                            const std::string msg) {
  DrawRectangleRec(dst, tint);
  DrawText(msg.c_str(), dst.x, dst.y, 1, WHITE);
}


void yumeami::draw_texture_tiled(const CameraBounds &cam_bounds,
                                 const SafeTex &tex, const Vector2 spacing,
                                 const Rectangle src, const Rectangle dst,
                                 const Vector2 origin, const float rotation,
                                 const Color tint) {
  float current_y_pos = dst.y;
  while (current_y_pos >= cam_bounds.top) {
    current_y_pos -= spacing.y;
  }

  while (current_y_pos <= cam_bounds.bottom) {
    Rectangle offset_y_dst = {
        .x = dst.x,
        .y = current_y_pos,
        .width = dst.width,
        .height = dst.height,
    };
    draw_texture_row(cam_bounds, tex, spacing, src, offset_y_dst, origin,
                     rotation, tint);
    current_y_pos += spacing.y;
  };
}


void yumeami::draw_fallback_tiled(const CameraBounds &cam_bounds,
                                  const Vector2 spacing, const Rectangle dst,
                                  const Color tint, const std::string msg) {
  float current_y_pos = dst.y;
  while (current_y_pos >= cam_bounds.top) {
    current_y_pos -= spacing.y;
  }

  while (current_y_pos <= cam_bounds.bottom) {
    Rectangle offset_y_dst = {
        .x = dst.x,
        .y = current_y_pos,
        .width = dst.width,
        .height = dst.height,
    };
    draw_fallback_row(cam_bounds, spacing, offset_y_dst, tint, msg);
    current_y_pos += spacing.y;
  };
}
