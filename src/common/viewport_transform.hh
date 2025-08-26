#include "raylib.h"
namespace yumeami {

  struct ViewportTransform {
    Rectangle src;
    Rectangle dst;
  };

  /**
   * @brief Calculate the highest possible integer scaling factor that enables
   * drawing the entire viewport on the window, and update ViewportTransform
   * accordingly.
   *
   * @param vp
   * @param transform
   */
  void calc_viewport_transform(const RenderTexture &vp,
                               ViewportTransform &transform);

  /**
   * @brief Draw viewport on raylib window.
   * @param vp
   * @param transform
   */
  void draw_viewport(const RenderTexture &vp,
                     const ViewportTransform &transform);

} // namespace yumeami
