#include "render/core/raylib_tx.hh"
#include "common/raii/texture.hh"
#include "common/units/px.hh"
#include "common/units/tx.hh"
#include <cmath>
#include <raylib.h>


namespace {
  using namespace yumeami;


  Vector2 scale_vec(px tx_scale, Vector2 vec) {
    return {
        .x = std::floorf(vec.x * (float)tx_scale),
        .y = std::floorf(vec.y * (float)tx_scale),
    };
  }


  Rectangle scale_rec(px tx_scale, Rectangle rec) {
    return {
        .x = std::floorf(rec.x * (float)tx_scale),
        .y = std::floorf(rec.y * (float)tx_scale),
        .width = std::floorf(rec.width * (float)tx_scale),
        .height = std::floorf(rec.height * (float)tx_scale),
    };
  }

  float scale_val(px tx_scale, tx val) {
    return std::floorf((float)tx_scale * (float)val);
  }


} // namespace


void yumeami::draw_pixel_tx(px tx_scale, Vector2 position, Color color) {
  DrawRectangleV(scale_vec(tx_scale, position), {tx_scale, tx_scale}, color);
}


void yumeami::draw_line_tx(px tx_scale, Vector2 startPos, Vector2 endPos,
                           Color color) {
  DrawLineV(scale_vec(tx_scale, startPos), scale_vec(tx_scale, endPos), color);
}


void yumeami::draw_circle_tx(px tx_scale, Vector2 center, tx radius,
                             Color color) {
  DrawCircleV(scale_vec(tx_scale, center), scale_val(tx_scale, radius), color);
}


void yumeami::draw_circle_lines_tx(px tx_scale, Vector2 center, tx radius,
                                   Color color) {
  DrawCircleLinesV(scale_vec(tx_scale, center), scale_val(tx_scale, radius),
                   color);
}


void yumeami::draw_circle_sector_tx(px tx_scale, Vector2 center, tx radius,
                                    float startAngle, float endAngle,
                                    int segments, Color color) {
  DrawCircleSector(scale_vec(tx_scale, center), scale_val(tx_scale, radius),
                   startAngle, endAngle, segments, color);
}


void yumeami::draw_circle_sector_lines_tx(px tx_scale, Vector2 center,
                                          tx radius, float startAngle,
                                          float endAngle, int segments,
                                          Color color) {
  DrawCircleSectorLines(scale_vec(tx_scale, center),
                        scale_val(tx_scale, radius), startAngle, endAngle,
                        segments, color);
}


void yumeami::draw_rectangle_tx(px tx_scale, Rectangle rec, Vector2 origin,
                                float rotation, Color color) {
  DrawRectanglePro(scale_rec(tx_scale, rec), scale_vec(tx_scale, origin),
                   rotation, color);
}


void yumeami::draw_rectangle_lines_tx(px tx_scale, Rectangle rec, Color color) {
  DrawRectangleLinesEx(scale_rec(tx_scale, rec), 1, color);
}


void yumeami::draw_texture_tx(px tx_scale, SafeTexture &texture,
                              Vector2 position, Color tint) {
  DrawTextureEx(texture, scale_vec(tx_scale, position), 0, (float)tx_scale,
                tint);
}


void yumeami::draw_texture_ex_tx(px tx_scale, SafeTexture &texture,
                                 Vector2 position, float rotation, float scale,
                                 Color tint) {
  DrawTextureEx(texture, scale_vec(tx_scale, position), rotation,
                scale_val(tx_scale, scale), tint);
}


void yumeami::draw_texture_pro_tx(px tx_scale, SafeTexture &texture,
                                  Rectangle source, Rectangle dest,
                                  Vector2 origin, float rotation, Color tint) {
  DrawTexturePro(texture, source, scale_rec(tx_scale, dest),
                 scale_vec(tx_scale, origin), rotation, tint);
}


void yumeami::draw_text_tx(px tx_scale, const std::string text, tx posX,
                           tx posY, tx fontSize, Color color) {
  DrawText(text.c_str(), scale_val(tx_scale, posX), scale_val(tx_scale, posY),
           scale_val(tx_scale, fontSize), color);
}


void yumeami::draw_text_tx_raw(px tx_scale, const std::string text, tx posX,
                               tx posY, px fontSize, Color color) {
  DrawText(text.c_str(), scale_val(tx_scale, posX), scale_val(tx_scale, posY),
           fontSize, color);
}
