/**
 * @file texture.hh
 * @brief Texture management. Handles ONLY texture management, does not contain drawing
 * functions.
 */

#pragma once
#include "raylib.h"
#include "util/units.hh"
#include <memory>

namespace yumeami {

  /**
   * @class SpxVector
   * @brief 2D Vector of spritepx_int
   *
   */
  struct SpxVector {
    spx_int x;
    spx_int y;
  };

  /**
   * @class Spritesheet
   * @brief Base spritesheet data.
   *
   */
  struct Spritesheet {
    Texture texture;       // spritesheet texture
    int rows;              // height in sprites
    int columns;           // width in sprites
    SpxVector sprite_size; // size of a sprite
  };

  /**
   * @class Sprite
   * @brief Reference to spritesheet and current sprite index. In case of a collection of
   * animations, each row must be 1 animation.
   *
   */
  struct Sprite {
    std::shared_ptr<Spritesheet> spritesheet_ptr;
    int row_index;
    int column_index;
  };

  /**
   * @brief Create a spritesheet. Automatically detects the maximum amount of rows and
   * columns possible.
   *
   * @param texture
   * @param sprite_size
   * @return spritesheet
   */
  Spritesheet create_spritesheet(Texture &texture, SpxVector sprite_size);

  /**
   * @brief Create a shared pointer containing a new spritesheet.
   * @param texture
   * @param sprite_size
   */
  std::shared_ptr<Spritesheet> create_spritesheet_ptr(Texture &texture,
                                                      SpxVector sprite_size);

  /**
   * @brief Calculate rectangle that corresponds to the specified sprite.
   * @param row_index row index of sprite
   * @param column_index column index of sprite
   * @param spritesheet
   * @return frame rectangle
   */
  Rectangle calc_spritesheet_rec(int row_index, int column_index,
                                 const Spritesheet &spritesheet);

  /**
   * @brief Calculate rectangle that corresponds to the specified sprite.
   * @param sprite
   * @param spritesheet
   * @return frame rectangle
   */
  Rectangle calc_spritesheet_rec(const Sprite &sprite);

} // namespace yumeami
