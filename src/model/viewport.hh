#pragma once
#include "common/raii/fwd.hh"
#include "common/raii/render_texture.hh"
#include "common/units/px.hh"
#include "common/units/tx.hh"
#include "resources/fwd.hh"
#include <entt/core/hashed_string.hpp>
#include <entt/resource/resource.hpp>
namespace yumeami {

  const entt::hashed_string VIEWPORT_RT_ID = "VIEWPORT";

  struct Viewport {
    tx width;
    tx height;
    px tx_scale;
    entt::resource<SafeRenderTexture> rt;
    Viewport(tx width, tx height, px tx_scale,
             SafeRenderTextureCache &rt_cache);
  };

} // namespace yumeami
