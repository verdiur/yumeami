#include "display_manager.hh"
#include "raylib.h"
#include <algorithm>

namespace yumeami {

DisplayManager::DisplayManager(RenderTexture& virtual_target)
  : p_virtual_target(&virtual_target)
  , m_src_rect(0, 0, virtual_target.texture.width, -virtual_target.texture.height)
  , m_dst_rect()
{
  const int virtual_width = virtual_target.texture.width;
  const int virtual_height = virtual_target.texture.height;

  const int scale_factor =
    std::min(GetScreenWidth() / virtual_width, GetScreenHeight() / virtual_height);

  m_dst_rect.x = (float)(GetScreenWidth() - virtual_width * scale_factor) / 2;
  m_dst_rect.y = (float)(GetScreenHeight() - virtual_height * scale_factor) / 2;
  m_dst_rect.width = virtual_width * scale_factor;
  m_dst_rect.height = virtual_height * scale_factor;
}

void
display_manager::draw_virtual_target(const DisplayManager& display_manager)
{
  BeginDrawing();
  DrawTexturePro(display_manager.p_virtual_target->texture,
                 display_manager.m_src_rect,
                 display_manager.m_dst_rect,
                 { 0, 0 },
                 0,
                 WHITE);
  EndDrawing();
}

} // namespace yumeami
