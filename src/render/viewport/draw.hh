#pragma once
#include "model/viewport/fwd.hh"
namespace yumeami {

  /**
   * @brief Draw viewport centered on the window
   * @param vp
   */
  void draw_viewport(Viewport &vp);

  void begin_viewport_texture_mode(Viewport &vp);
  void end_viewport_texture_mode();

} // namespace yumeami
