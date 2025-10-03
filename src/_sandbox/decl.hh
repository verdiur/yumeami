#pragma once
#include "logic/world.hh"
#include "resman/spritesheet.hh"
#include "resman/texture.hh"
namespace yumeami::sandbox {

  World create_spritesheet_world(SheetCache &cache);
  World create_wrap_world(SheetCache &cache);
  World create_collision_world();
  World create_sprite_position_world(SheetCache &cache);
  World create_zorder_world(SheetCache &cache);
  World create_random_move_world(SheetCache &cache);
  World create_animation_world(SheetCache &cache);
  World create_background_world(SheetCache &sheet_cache,
                                TextureCache &tex_cache);

} // namespace yumeami::sandbox
