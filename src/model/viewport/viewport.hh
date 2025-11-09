#pragma once
#include "common/raii/fwd.hh"
#include "common/units/px.hh"
#include "common/units/tx.hh"
#include "resources/render_texture/fwd.hh"
#include <entt/resource/resource.hpp>
#include <entt/signal/fwd.hpp>
#include <optional>

namespace yumeami {

  /**
   * @class Viewport
   * @brief The viewport on the window.
   *
   */
  struct Viewport {
    tx width;   // width of the viewport in tx
    tx height;  // height of the viewport in tx
    px tx_size; // amount of px that 1 tx corresponds to
    entt::resource<SafeRenderTexture> render_texture;

    static std::optional<Viewport> create(tx width, tx height, px tx_scale,
                                          SafeRenderTextureCache &rt_cache);

    /**
     * @brief Update the viewport size. This will delete and replace the
     * corresponding SafeRenderTexture, and update the viewport's
     * SafeRenderTexture handle. Pointers to the render texture will become
     * invalid.
     *
     * @param vp
     */
    void update_viewport_size(SafeRenderTextureCache &rt_cache,
                              entt::dispatcher &dispatcher);

  private:
    /**
     * @brief Viewport constructor. Throws if loading the SafeRenderTexture
     * fails.
     *
     * @param width width of the viewport in tx
     * @param height height of the viewport in tx
     * @param tx_scale how many px is 1 tx?
     * @param rt_pool SafeRenderTexture pool
     */
    Viewport(tx width, tx height, px tx_scale,
             SafeRenderTextureCache &rt_cache);
  };

  struct ViewportSizeUpdatedEvent {};

  /**
   * @brief Calculate the largest possible texel size that enables drawing
   * the entire viewport on the window. The result will be quantized per
   * 1/VIEWPORT_SCALE_DENOMINATOR. If the result is smaller than 1, then the
   * function will return 1.
   *
   * @param vp
   * @return texel scaling factor
   */
  px calc_best_tx_size(tx rt_width, tx rt_height);

} // namespace yumeami
