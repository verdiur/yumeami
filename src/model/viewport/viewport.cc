#include "model/viewport/viewport.hh"
#include "common/defines.hh"
#include "resources/core/id.hh"
#include "resources/render_texture/cache.hh"
#include <entt/signal/dispatcher.hpp>
#include <optional>
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <stdexcept>


yumeami::Viewport::Viewport(tx width, tx height, px tx_scale,
                            SafeRenderTextureCache &rt_cache)
    : width(width), height(height), tx_size(tx_scale) {

  auto ret = rt_cache.load(generate_id(), (int)width * (int)tx_scale,
                           (int)height * (int)tx_scale);
  if (!ret.second) {
    std::runtime_error("[Viewport] could not load RenderTexture");
  }
  render_texture = ret.first->second;
}


std::optional<yumeami::Viewport>
yumeami::Viewport::create(tx width, tx height, px tx_scale,
                          SafeRenderTextureCache &rt_cache) {
  try {
    return Viewport(width, height, tx_scale, rt_cache);

  } catch (std::runtime_error &err) {
    spdlog::error("{}", err.what());
    return std::nullopt;
  }
}


void yumeami::Viewport::update_viewport_size(SafeRenderTextureCache &rt_cache,
                                             entt::dispatcher &dispatcher) {
  tx_size = calc_best_tx_size(width, height);
  auto ret = rt_cache.force_load(generate_id(), (int)width * (int)tx_size,
                                 (int)height * (int)tx_size);
  if (!ret.second) {
    std::runtime_error("[Viewport] could not load RenderTexture");
  }
  render_texture = ret.first->second;
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
