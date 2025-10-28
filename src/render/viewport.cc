#include "render/viewport.hh"
#include "common/viewport/viewport.hh"
#include "raylib.h"
#include <common/units/tx.hh>


void yumeami::draw_viewport(const Viewport &vp) {
  float tx_scale = vp.tx_scale;
  Vector2 pos = {
      .x = (GetScreenWidth() - (float)vp.get_width() * tx_scale) / 2.0f,
      .y = (GetScreenHeight() - (float)vp.get_height() * tx_scale) / 2.0f,
  };

  DrawTextureEx(vp.rt->texture, pos, 0, vp.tx_scale, WHITE);
}
