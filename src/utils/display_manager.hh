#pragma once
#include "raylib.h"

namespace yumeami {
namespace display {

  struct DisplayManager
  {
    DisplayManager(RenderTexture& virtual_target);

    RenderTexture* const p_virtual_target;
    Rectangle src_rect;
    Rectangle dst_rect;
  };

  void draw_virtual_target(const DisplayManager& display_manager);

} // namespace display
} // namespace yumeami
