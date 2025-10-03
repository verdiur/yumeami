/**
 * @file base.hh
 * @brief Common drawing elements
 */

#pragma once
#include "logic/camera.hh"
#include "raylib.h"
namespace yumeami {

  const Color COLOR_NO_SPRITE = BLUE;
  const Color COLOR_NO_SHEET = MAGENTA;

  const Color COLOR_HITBOX = WHITE;
  const Color COLOR_GUIDE = DARKGRAY;
  const Color COLOR_FACING = GREEN;
  const Color COLOR_ERROR = MAROON;

  const Color COLOR_DEBUG_TEXT = GREEN;

  /**
   * @brief Draws a texture in a tile pattern, across the camera.
   * @param bounds Camera bounds
   * @param callback Draw callback
   * @param spacing Spacing in pixels
   */
  void draw_texture_tiled(const CameraBounds &bounds, const Vector2 spacing,
                          const SafeTex &texture, const Rectangle src,
                          const Rectangle dst, const Vector2 origin,
                          const float rotation, const Color tint);

  void draw_fallback_tiled(const CameraBounds &bounds, const Vector2 spacing,
                           const Rectangle dst, const Color tint,
                           const std::string msg);

} // namespace yumeami
