#pragma once
#include "raylib.h"

namespace yumeami {

class DisplayManager
{
public:
  DisplayManager(RenderTexture& virtual_target);

public:
  RenderTexture* const p_virtual_target;
  Rectangle m_src_rect;
  Rectangle m_dst_rect;
};

namespace display_manager {
  void draw_virtual_target(const DisplayManager& display_manager);
}

} // namespace yumeami
