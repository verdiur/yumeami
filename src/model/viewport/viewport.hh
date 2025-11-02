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
    tx width;   // width of the viewport in tx
    tx height;  // height of the viewport in tx
    px tx_size; // amount of px that 1 tx corresponds to

  private:
    entt::resource<SafeRenderTexture>
        render_texture_handle; // render texture. measured in px.

  public:
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

    /**
     * @brief Get raw reference to SafeRenderTexture.
     * @warning Do not store this reference long-term, as it can be invalidated
     * at any time by window resizing.
     * @return SafeRenderTexture
     */
    SafeRenderTexture &render_texture();
    const SafeRenderTexture &render_texture() const;

    /**
     * @brief Update the viewport size. This will delete and replace the
     * corresponding SafeRenderTexture, and update the viewport's
     * SafeRenderTexture handle. Pointers to the render texture will become
     * invalid.
     *
     * @param vp
     */
    void update_viewport_size(SafeRenderTextureCache &rt_cache);
  };

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
