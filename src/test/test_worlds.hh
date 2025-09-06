#pragma once

#include "assetmgr/texture.hh"
#include "logic/world.hh"

namespace yumeami::test {

  World test_create_world();
  World test_spritesheet_world(SheetPool &pool);

} // namespace yumeami::test
