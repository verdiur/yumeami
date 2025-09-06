#include "test/test_worlds.hh"
#include "assetmgr/texture.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include <stdexcept>


yumeami::World yumeami::test::test_create_world() {
  World world{
      .width = 20,
      .height = 15,
      .tile_size = 16,
      .wrap = false,
      .scale = 2,
      .reg = {},
      .sheet_ids = {},
  };
  auto ent = world.reg.create();
  world.reg.emplace<TruePos>(ent, 1, 1);
  world.reg.emplace<DrawPos>(ent, 1, 1);
  // world.reg.emplace<Sprite>(ent, "this will not work", 0, 0);

  auto player = world.reg.create();
  world.reg.emplace<TruePos>(player, 0, 0);
  world.reg.emplace<DrawPos>(player, 0, 0);
  world.reg.emplace<MovementState>(player);
  world.reg.emplace<Velocity>(player, 0.4f);
  world.reg.emplace<PlayerTag>(player);

  return world;
}


yumeami::World yumeami::test::test_spritesheet_world(SheetPool &pool) {
  pool.load_sheet("assets/test_sprsh.png", 16, 16, "test_spritesheet");
  World world{
      .width = 20,
      .height = 15,
      .tile_size = 16,
      .wrap = false,
      .scale = 2,
      .reg = {},
      .sheet_ids = {"test_spritesheet"},
  };
  Sheet *sheet = pool.get_sheet("test_spritesheet");
  if (!sheet) {
    throw std::runtime_error("erm...");
  }

  for (int r = 0; r < sheet->rows - 5; r++) {
    for (int c = 0; c < sheet->cols - 4; c++) {
      auto ent = world.reg.create();
      world.reg.emplace<DrawPos>(ent, c, r);
      world.reg.emplace<Sprite>(ent, "test_spritesheet", r, c);
    }
  }

  return world;
}
