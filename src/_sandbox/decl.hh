#pragma once
#include "logic/world.hh"
#include "resman/spritesheet.hh"
namespace yumeami::sandbox {

  World create_spritesheet_world(SheetCache &cache);
  World create_wrap_world(SheetCache &cache);
  World create_collision_world();
  World create_sprite_position_world(SheetCache &cache);
  World create_zorder_world(SheetCache &cache);
  World create_random_move_world();

} // namespace yumeami::sandbox
