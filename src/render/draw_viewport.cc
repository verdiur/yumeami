#include "render/draw_viewport.hh"
#include "common/raii/render_texture.hh"
#include "model/viewport.hh"
#include <raylib.h>


void yumeami::draw_viewport(Viewport &vp) {
  SafeRenderTexture &rt = vp.render_texture();
  int rt_width = rt->texture.width;
  int rt_height = rt->texture.height;

  Rectangle src{
      .x = 0,
      .y = 0,
      .width = (float)rt_width,
      .height = -(float)rt_height,
  };
  Rectangle dst{
      .x = (GetScreenWidth() - (float)rt_width) / 2,
      .y = (GetScreenHeight() - (float)rt_height) / 2,
      .width = (float)rt_width,
      .height = (float)rt_height,
  };

  DrawTexturePro(rt->texture, src, dst, {0, 0}, 0, WHITE);
}
