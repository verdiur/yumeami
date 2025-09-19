#pragma once
#include "logic/world.hh"
#include "resman/spritesheet.hh"
namespace yumeami::_sandbox {

  World create_spritesheet_world(SheetCache &cache);
  World create_wrap_world(SheetCache &cache);
  World create_collision_world();

} // namespace yumeami::_sandbox
