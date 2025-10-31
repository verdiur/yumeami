#include "model/viewport.hh"
#include "common/raii/render_texture.hh"
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
