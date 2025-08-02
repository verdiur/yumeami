/**
 * @file viewport_transform.hh
 * @brief Data struct for viewport transforms
 */

#include "raylib.h"

namespace yumeami {

struct ViewportTransform {
  Rectangle src_rect = {};
  Rectangle dst_rect = {};
};

/**
 * @brief Calculate the highest possible integer scaling factor that allows to
 * draw the entire viewport on the window, and modifies the ViewportTransform
 * accordingly.
 *
 * @param viewport
 * @param viewport_transform
 */
void calc_viewport_scaling(const RenderTexture &viewport,
                           ViewportTransform &viewport_transform);

void draw_viewport(const RenderTexture &viewport,
                   const ViewportTransform &viewport_transform);

} // namespace yumeami
