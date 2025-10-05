/**
 * @file base.hh
 * @brief Common drawing elements
 */

#pragma once
#include "logic/camera.hh"
#include "raylib.h"
namespace yumeami {

  /* COLOR DEFINITIONS ********************************************************/

  const Color COLOR_NO_SPRITE = BLUE;
  const Color COLOR_NO_SHEET = MAGENTA;

  const Color COLOR_HITBOX = WHITE;
  const Color COLOR_GUIDE = DARKGRAY;
  const Color COLOR_FACING = GREEN;
  const Color COLOR_ERROR = MAROON;

  const Color COLOR_DEBUG_TEXT = GREEN;

  /****************************************************************************/

  /**
   * @brief Draws a "fallback" rectangle. Used for placeholder rendering if
   * something goes wrong.
   * @param dst Destination rectangle
   * @param tint
   * @param msg Message to display
   */
  void draw_fallback(const Rectangle dst, const Color tint,
                     const std::string msg);

  /**
   * @brief Draws a texture in a tile pattern, across the camera
   * @param bounds Camera bounds
   * @param callback Draw callback
   * @param spacing Spacing in pixels
   */
  /**
   * @brief Draws a texture in a tile pattern, across the camera
   * @param cam_bounds Camera bounds
   * @param tex Texture to draw
   * @param spacing Tile spacing
   * @param src Source rectangle
   * @param dst Destination rectangle
   * @param origin Center origin
   * @param rotation
   * @param tint
   */
  void draw_texture_tiled(const CameraBounds &cam_bounds, const SafeTex &tex,
                          const Vector2 spacing, const Rectangle src,
                          const Rectangle dst, const Vector2 origin,
                          const float rotation, const Color tint);

  /**
   * @brief Draws a "fallback" rectangle in a tile pattern, accros the camera
   * @param cam_bounds Camera bounds
   * @param spacing Spacing in pixels
   * @param dst Destination rectangle
   * @param tint
   * @param msg Message to display
   */
  void draw_fallback_tiled(const CameraBounds &bounds, const Vector2 spacing,
                           const Rectangle dst, const Color tint,
                           const std::string msg);

} // namespace yumeami
