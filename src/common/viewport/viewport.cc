#include "common/viewport/viewport.hh"
#include "common/defines.hh"
#include "common/raii/render_texture.hh"
#include "common/units/tx.hh"
#include <algorithm>
#include <cmath>
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>


yumeami::Viewport::Viewport(tx width, tx height)
    : rt(SafeRenderTexture(width, height)), tx_scale(1) {}


yumeami::tx yumeami::Viewport::get_width() const { return rt->texture.width; }
yumeami::tx yumeami::Viewport::get_height() const { return rt->texture.height; }


float yumeami::calc_viewport_texel_scale(const Viewport &vp) {
  tx vp_width = vp.get_width();
  tx vp_height = vp.get_height();

  float width_ratio = (float)GetScreenWidth() / (float)vp_width;
  float height_ratio = (float)GetScreenHeight() / (float)vp_height;
  float raw_scale = std::min(width_ratio, height_ratio);

  float quantized_scale =
      std::floor(raw_scale * VIEWPORT_SCALE_BASE) * VIEWPORT_SCALE_BASE;

  return (quantized_scale >= 1.0f) ? quantized_scale : 1.0f;
}


float yumeami::update_viewport_texel_scale(Viewport &vp,
                                           entt::dispatcher &dispatcher) {
  float scale = calc_viewport_texel_scale(vp);
  vp.tx_scale = scale;
  dispatcher.trigger(ViewportScaleUpdatedEvent{&vp});
  return scale;
}
