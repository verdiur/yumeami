#include "display_manager.hh"
#include "raylib.h"
#include <algorithm>

namespace yumeami {

void
setup_display_manager(const RenderTexture& virtual_target,
                      DisplayManager& display_manager)
{
  // calculate scaling
  const int virtual_width = virtual_target.texture.width;
  const int virtual_height = virtual_target.texture.height;
  const int scale_factor =
    std::min(GetScreenWidth() / virtual_width, GetScreenHeight() / virtual_height);

  // setup transform rectangles
  display_manager.src_rect = {
    0, 0, (float)virtual_target.texture.width, -(float)virtual_target.texture.height
  };

  display_manager.dst_rect = {
    (float)(GetScreenWidth() - virtual_width * scale_factor) / 2,
    (float)(GetScreenHeight() - virtual_height * scale_factor) / 2,
    (float)virtual_width * scale_factor,
    (float)virtual_height * scale_factor,
  };
}

void
draw_virtual_target_on_window(const RenderTexture& virtual_target,
                              const DisplayManager& display_manager)
{
  BeginDrawing();
  DrawTexturePro(virtual_target.texture,
                 display_manager.src_rect,
                 display_manager.dst_rect,
                 { 0, 0 },
                 0,
                 WHITE);
  EndDrawing();
}

} // namespace yumeami
