#pragma once
#include "common/raii/render_texture.hh"
#include "common/units/fwd.hh"
#include "common/units/px.hh"
#include <entt/signal/fwd.hpp>
namespace yumeami {

  /**
   * @class Viewport
   * @brief Viewport on which to draw. The viewport itself is a simple
   * SafeRenderTexture.
   *
   */
  struct Viewport {
    SafeRenderTexture rt;
    px tx_scale;
    Viewport(tx width, tx height);
    tx get_width() const;
    tx get_height() const;
  };

  /**
   * @class ViewportScaledEvent
   * @brief The viewport scale has been updated
   *
   */
  struct ViewportScaleUpdatedEvent {
    Viewport *vp;
  };

  /**
   * @brief Calculate the highest possible texel scaling factor that enables
   * drawing the entire viewport on the window, and update ViewportTransform
   * accordingly. The scale will be quantized to increments of
   * 1/VIEWPORT_SCALE_BASE.
   *
   * @param vp
   * @return viewport scale
   */
  float calc_viewport_texel_scale(const Viewport &vp);

  /**
   * @brief Same as calc_viewport_texel_scale, but updates the viewport scale as
   * well.
   *
   * @param vp
   * @return viewport scale
   */
  float update_viewport_texel_scale(Viewport &vp, entt::dispatcher &dispatcher);

} // namespace yumeami
