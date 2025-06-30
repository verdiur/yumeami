#include "display_manager.hh"
#include "raylib.h"
#include <algorithm>

namespace yumeami {
namespace display {

  DisplayManager::DisplayManager(RenderTexture& virtual_target)
    : p_virtual_target(&virtual_target)
    , src_rect(0, 0, virtual_target.texture.width, -virtual_target.texture.height)
    , dst_rect()
  {
    const int virtual_width = virtual_target.texture.width;
    const int virtual_height = virtual_target.texture.height;

    const int scale_factor =
      std::min(GetScreenWidth() / virtual_width, GetScreenHeight() / virtual_height);

    dst_rect.x = (float)(GetScreenWidth() - virtual_width * scale_factor) / 2;
    dst_rect.y = (float)(GetScreenHeight() - virtual_height * scale_factor) / 2;
    dst_rect.width = virtual_width * scale_factor;
    dst_rect.height = virtual_height * scale_factor;
  }

  void draw_virtual_target(const DisplayManager& display_manager)
  {
    BeginDrawing();
    DrawTexturePro(display_manager.p_virtual_target->texture,
                   display_manager.src_rect,
                   display_manager.dst_rect,
                   { 0, 0 },
                   0,
                   WHITE);
    EndDrawing();
  }
} // namespace display

} // namespace yumeami
