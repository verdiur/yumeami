#include "_sandbox/world.hh"
#include "entt/entity/fwd.hpp"
#include "logic/components.hh"
#include "logic/world.hh"
#include <stdexcept>


yumeami::World yumeami::_sandbox::create_spritesheet_world(SheetPool &pool) {
  pool.load("test", "resources/test_sprsh.png", 16, 16);
  Sheet *sheet = pool.get("test");

  if (!sheet) {
    throw std::runtime_error("spritesheet loading failed");
  }

  World world{
      .width = 20,
      .height = 15,
      .tile_size = 16,
      .wrap = false,
      .scale = 2,
      .sheet_ids = {"test"},
  };

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = world.reg.create();
      world.reg.emplace<DrawPos>(e, c, r);
      world.reg.emplace<Sprite>(e, "test", r, c);
    }
  }

  return world;
}
