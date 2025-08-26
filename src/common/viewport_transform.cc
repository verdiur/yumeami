#include "common/viewport_transform.hh"
#include "raylib.h"
#include <algorithm>

void yumeami::calc_viewport_transform(const RenderTexture &vp,
                                      ViewportTransform &transform) {
  int vp_width = vp.texture.width;
  int vp_height = vp.texture.height;
  int scale =
      std::min(GetScreenWidth() / vp_width, GetScreenHeight() / vp_height);

  transform.src = Rectangle{
      0,
      0,
      static_cast<float>(vp_width),
      -static_cast<float>(vp_height),
  };
  transform.dst = Rectangle{
      static_cast<float>(GetScreenWidth() - vp_width * scale) / 2,
      static_cast<float>(GetScreenHeight() - vp_height * scale) / 2,
      static_cast<float>(vp_width * scale),
      static_cast<float>(vp_height * scale),
  };
}

void yumeami::draw_viewport(const RenderTexture &vp,
                            const ViewportTransform &transform) {
  DrawTexturePro(vp.texture, transform.src, transform.dst, {}, 0, WHITE);
}
