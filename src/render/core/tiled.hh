#pragma once
#include "common/types/fwd.hh"
#include "common/types/vector.hh"
#include "model/camera/fwd.hh"
#include <functional>
namespace yumeami {

  /**
   * @brief Call draw_func multiple times, tiling it by the specified spacing,
   * spanning the entire camera surface.
   *
   * @param cam_bounds
   * @param spacing
   * @param draw_func function to call. Its parameter is the draw position in
   * tx.
   */
  void draw_tiled_tx(const CameraBounds &cam_bounds, TexelVector2 spacing,
                     TexelVector2 offset,
                     std::function<void(TexelVector2)> draw_func);

} // namespace yumeami
