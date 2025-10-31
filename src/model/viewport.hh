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

  /**
   * @class Viewport
   * @brief The viewport on the window.
   *
   */
  struct Viewport {
    tx width;                             // width of the viewport in tx
    tx height;                            // height of the viewport in tx
    px tx_scale;                          // how many px is 1 tx?
    entt::resource<SafeRenderTexture> rt; // render texture. measured in px.

    /**
     * @brief Viewport constructor. Throws if loading the SafeRenderTexture
     * fails.
     *
     * @param width width of the viewport in tx
     * @param height height of the viewport in tx
     * @param tx_scale how many px is 1 tx?
     * @param rt_cache SafeRenderTexture cache
     */
    Viewport(tx width, tx height, px tx_scale,
             SafeRenderTextureCache &rt_cache);
  };

} // namespace yumeami
