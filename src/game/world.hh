#pragma once
#include "entt/entt.hpp"
#include "raylib.h"
#include "units.hh"

namespace yumeami {

/**
 * @class WorldMeta
 * @brief World metadata.
 *
 */
struct WorldMeta
{
  std::string name;
  std::string author;
  std::string description;
};

/**
 * @class World
 * @brief Represents a dream world.
 *
 * NOTE: Yume Nikki draws its worlds with a scale factor of 2 (which means that sprites
 * are drawn at twice the size they are defined). For example, a 20*15 tiles with a tile
 * size of 16px (320*240px) is drawn as 640*480px. Yume Ami mirrors this behavior.
 *
 */
struct World
{
  // assets

  // dimensions
  const tile_int width = 20;
  const tile_int height = 15;
  const sprite_pixel_int tile_size = 16;
  const int sprite_pixel_multiplier = 2;

  // state
  entt::registry registry = {};
};

/**
 * @brief Draw world on a RenderTexture.
 *
 * @param world
 */
void
draw_world(World& world, RenderTexture& target);

/**
 * @brief DEBUG FUNCTION
 * This function will be removed later.
 *
 * @return World
 */
World
create_dummy_world();

} // namespace yumeami
