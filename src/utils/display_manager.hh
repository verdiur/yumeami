#pragma once
#include "raylib.h"

namespace yumeami {

/**
 * @class DisplayManager
 * @brief Interface between a virtual RenderTexture target and the raylib window. Contains
 * information for scaling a virtual target.
 *
 */
struct DisplayManager
{
  Rectangle src_rect = {};
  Rectangle dst_rect = {};
};

/**
 * @brief Calculates the highest possible integer scaling factor that can draw the
 * entire virtual target on the window, and setups the display manager accordingly.
 *
 * @param display_manager
 */
void
setup_display_manager(const RenderTexture& virtual_target,
                      DisplayManager& display_manager);

/**
 * @brief Scales and draws the virtual target on the window.
 *
 * @param display_manager
 */
void
draw_virtual_target_on_window(const RenderTexture& virtual_target,
                              const DisplayManager& display_manager);

} // namespace yumeami
