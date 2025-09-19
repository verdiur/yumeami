#pragma once
#include "logic/world.hh"
#include "resman/spritesheet.hh"
namespace yumeami::_sandbox {

  World create_spritesheet_world(SheetCache &cache);
  World create_wrap_world(SheetCache &cache);
  World create_collision_world();
  World create_sprite_position_world(SheetCache &cache);

} // namespace yumeami::_sandbox
