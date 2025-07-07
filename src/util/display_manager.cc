#include "display_manager.hh"
#include "raylib.h"
#include <algorithm>

void
yumeami::setup_display_manager(const RenderTexture& virtual_target,
                               DisplayManager& display_manager)
{
  // calculate scaling
  const int virtual_width = virtual_target.texture.width;
  const int virtual_height = virtual_target.texture.height;
  const int scale_factor =
    std::min(GetScreenWidth() / virtual_width, GetScreenHeight() / virtual_height);

  // setup transform rectangles
  display_manager.src_rect = { 0,
                               0,
                               static_cast<float>(virtual_target.texture.width),
                               -static_cast<float>(virtual_target.texture.height) };

  display_manager.dst_rect = {
    static_cast<float>(GetScreenWidth() - virtual_width * scale_factor) / 2,
    static_cast<float>(GetScreenHeight() - virtual_height * scale_factor) / 2,
    static_cast<float>(virtual_width * scale_factor),
    static_cast<float>(virtual_height * scale_factor),
  };
}

void
yumeami::draw_virtual_target_on_window(const RenderTexture& virtual_target,
                                       const DisplayManager& display_manager)
{
  DrawTexturePro(virtual_target.texture,
                 display_manager.src_rect,
                 display_manager.dst_rect,
                 { 0, 0 },
                 0,
                 WHITE);
}
