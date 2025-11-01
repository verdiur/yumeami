#include "model/viewport.hh"
#include "common/defines.hh"
#include "common/raii/render_texture.hh"
#include "raylib.h"
#include "resources/render_texture_cache.hh"
#include <entt/core/hashed_string.hpp>
#include <spdlog/spdlog.h>


yumeami::Viewport::Viewport(tx width, tx height, px tx_scale,
                            SafeRenderTextureCache &rt_cache)
    : width(width), height(height), tx_scale(tx_scale) {

  auto ret = rt_cache.load(VIEWPORT_RT_ID, (int)width * (int)tx_scale,
                           (int)height * (int)tx_scale);
  if (!ret.second) {
    std::runtime_error("[Viewport] could not load RenderTexture");
  }
  render_texture_handle = ret.first->second;
}


yumeami::SafeRenderTexture &yumeami::Viewport::render_texture() {
  return *render_texture_handle.handle();
}


yumeami::px yumeami::calc_best_tx_scale(px rt_width, px rt_height) {
  float width_ratio = (float)GetScreenWidth() / (float)rt_width;
  float height_ratio = (float)GetScreenHeight() / (float)rt_height;

  float raw_scale = std::min(width_ratio, height_ratio);
  if (raw_scale <= 1) {
    return 1;
  }

  return std::floorf(raw_scale * VIEWPORT_SCALE_DENOMINATOR) /
         VIEWPORT_SCALE_DENOMINATOR;
}
