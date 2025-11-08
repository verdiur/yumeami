#include "model/viewport/viewport.hh"
#include "common/defines.hh"
#include "common/raii/render_texture.hh"
#include "resources/render_texture_cache.hh"
#include <entt/core/hashed_string.hpp>
#include <entt/signal/dispatcher.hpp>
#include <raylib.h>
#include <stdexcept>


yumeami::Viewport::Viewport(tx width, tx height, px tx_scale,
                            SafeRenderTexturePool &rt_pool)
    : width(width), height(height), tx_size(tx_scale) {
  auto ret =
      rt_pool.cache.load(rt_pool.counter.next(), (int)width * (int)tx_scale,
                         (int)height * (int)tx_scale);
  if (!ret.second) {
    std::runtime_error("[Viewport] could not load RenderTexture");
  }
  render_texture_handle = ret.first->second;
}


yumeami::SafeRenderTexture &yumeami::Viewport::render_texture() {
  return *render_texture_handle.handle();
}


const yumeami::SafeRenderTexture &yumeami::Viewport::render_texture() const {
  return *render_texture_handle.handle();
}


void yumeami::Viewport::update_viewport_size(SafeRenderTexturePool &rt_pool,
                                             entt::dispatcher &dispatcher) {
  tx_size = calc_best_tx_size(width, height);
  auto ret = rt_pool.cache.force_load(rt_pool.counter.next(),
                                      (int)width * (int)tx_size,
                                      (int)height * (int)tx_size);
  if (!ret.second) {
    std::runtime_error("[Viewport] could not load RenderTexture");
  }
  render_texture_handle = ret.first->second;
  dispatcher.trigger(ViewportSizeUpdatedEvent{});
}


yumeami::px yumeami::calc_best_tx_size(tx rt_width, tx rt_height) {
  float width_ratio = (float)GetScreenWidth() / (float)rt_width;
  float height_ratio = (float)GetScreenHeight() / (float)rt_height;

  float raw_scale = std::min(width_ratio, height_ratio);
  if (raw_scale <= 1) return 1;

  int denominator = YUMEAMI_VIEWPORT_SCALE_DENOMINATOR;
  return std::floorf(raw_scale * denominator) / denominator;
}
