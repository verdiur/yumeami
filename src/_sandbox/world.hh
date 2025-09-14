#pragma once
#include "logic/world.hh"
#include "resman/texture.hh"
namespace yumeami::_sandbox {

  World create_spritesheet_world(SheetPool &pool);
  World create_wrap_world(SheetPool &pool);
  World create_collision_world();

} // namespace yumeami::_sandbox
