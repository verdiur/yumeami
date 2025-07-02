/**
 * @file
 * @brief Unit-specific aliases for clarity. You should always use these instead of raw
 * primitive types where applicable.
 *
 * A SPRITE PIXEL is the size of 1 pixel from a sprite.
 * 1 SPRITE PIXEL == 2 pixels on the virtual target.
 *
 * A TILE corresponds to the side length of 1 tile.
 * 1 TILE == however many SPRITE PIXELS it's defined as. The default is 16 SPRITE PIXELS.
 */

#pragma once

namespace yumeami {

using sprite_pixel_int = int;
using tile_int = int;
using tile_float = float;

} // namespace yumeami
