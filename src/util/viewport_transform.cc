#include "viewport_transform.hh"
#include "raylib.h"
#include <algorithm>

// calc_viewport_scaling
void yumeami::calc_viewport_scaling(const RenderTexture &viewport,
                                    ViewportTransform &viewport_transform) {
  const int vp_width = viewport.texture.width;
  const int vp_height = viewport.texture.height;
  const int scale_factor =
      std::min(GetScreenWidth() / vp_width, GetScreenHeight() / vp_height);

  viewport_transform.src_rect = {0, 0, static_cast<float>(vp_width),
                                 static_cast<float>(vp_height)};
  viewport_transform.dst_rect = {
      static_cast<float>(GetScreenWidth() - vp_width * scale_factor) / 2,
      static_cast<float>(GetScreenHeight() - vp_height * scale_factor) / 2,
      static_cast<float>(vp_width * scale_factor),
      static_cast<float>(vp_height * scale_factor)};
}

// draw_viewport
void yumeami::draw_viewport(const RenderTexture &viewport,
                            const ViewportTransform &viewport_transform) {
  DrawTexturePro(viewport.texture, viewport_transform.src_rect,
                 viewport_transform.dst_rect, {0, 0}, 0, WHITE);
}
