#pragma once
#include "common/raii/fwd.hh"
#include "common/units/fwd.hh"
#include <raylib.h>
namespace yumeami {

  void draw_pixel_tx(px tx_scale, Vector2 position, Color color);
  void draw_line_tx(px tx_scale, Vector2 startPos, Vector2 endPos, Color color);

  void draw_circle_tx(px tx_scale, Vector2 center, tx radius, Color color);
  void draw_circle_lines_tx(px tx_scale, Vector2 center, tx radius,
                            Color color);

  void draw_circle_sector_tx(px tx_scale, Vector2 center, tx radius,
                             float startAngle, float endAngle, int segments,
                             Color color);
  void draw_circle_sector_lines_tx(px tx_scale, Vector2 center, tx radius,
                                   float startAngle, float endAngle,
                                   int segments, Color color);

  void draw_rectangle_tx(px tx_scale, Rectangle rec, Vector2 origin,
                         float rotation, Color color);
  void draw_rectangle_lines_tx(px tx_scale, Rectangle rec, Color color);

  void draw_texture_tx(px tx_scale, SafeTexture &texture, Vector2 position,
                       Color tint);
  void draw_texture_ex_tx(px tx_scale, SafeTexture &texture, Vector2 position,
                          float rotation, float scale, Color tint);
  /**
   * @brief Draw a texture with "pro" parameters in "texel mode"
   * @param tx_scale
   * @param texture
   * @param source source rectangle, in pixels
   * @param dest destination rectangle, in texels
   * @param origin origin in texels
   * @param rotation
   * @param tint
   */
  void draw_texture_pro_tx(px tx_scale, SafeTexture &texture, Rectangle source,
                           Rectangle dest, Vector2 origin, float rotation,
                           Color tint);

  // TODO: draw_texture_npatch_tx

} // namespace yumeami
