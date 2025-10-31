#include "render/core/raylib_tx.hh"
#include "common/raii/texture.hh"
#include "common/units/px.hh"
#include "common/units/tx.hh"
#include <raylib.h>


// TODO: floor or ceil scaled coordinates and dimensions to avoid irregular
// pixels


namespace {
  using namespace yumeami;


  Vector2 scale_vec(px tx_scale, Vector2 vec) {
    return {
        .x = vec.x * (float)tx_scale,
        .y = vec.y * (float)tx_scale,
    };
  }


  Rectangle scale_rec(px tx_scale, Rectangle rec) {
    return {
        .x = rec.x * (float)tx_scale,
        .y = rec.y * (float)tx_scale,
        .width = rec.width * (float)tx_scale,
        .height = rec.height * (float)tx_scale,
    };
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
  DrawCircleV(scale_vec(tx_scale, center), (float)radius * (float)tx_scale,
              color);
}


void yumeami::draw_circle_lines_tx(px tx_scale, Vector2 center, tx radius,
                                   Color color) {
  DrawCircleLinesV(scale_vec(tx_scale, center), (float)radius * (float)tx_scale,
                   color);
}


void yumeami::draw_circle_sector_tx(px tx_scale, Vector2 center, tx radius,
                                    float startAngle, float endAngle,
                                    int segments, Color color) {
  DrawCircleSector(scale_vec(tx_scale, center), (float)radius * (float)tx_scale,
                   startAngle, endAngle, segments, color);
}


void yumeami::draw_circle_sector_lines_tx(px tx_scale, Vector2 center,
                                          tx radius, float startAngle,
                                          float endAngle, int segments,
                                          Color color) {
  DrawCircleSectorLines(scale_vec(tx_scale, center),
                        (float)radius * (float)tx_scale, startAngle, endAngle,
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
                scale * (float)tx_scale, tint);
}


void yumeami::draw_texture_pro_tx(px tx_scale, SafeTexture &texture,
                                  Rectangle source, Rectangle dest,
                                  Vector2 origin, float rotation, Color tint) {
  DrawTexturePro(texture, source, scale_rec(tx_scale, dest),
                 scale_vec(tx_scale, origin), rotation, tint);
}
