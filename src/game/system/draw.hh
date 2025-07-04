#pragma once

#include "game/world.hh"
#include "raylib.h"

namespace yumeami::sys {

/**
 * @brief Draw world on a RenderTexture.
 *
 * @param world
 */
void
draw_world(World& world, RenderTexture& target);

} // namespace yumeami::sys
