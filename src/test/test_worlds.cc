#include "test/test_worlds.hh"
#include "logic/components.hh"
#include "logic/world.hh"

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

  return world;
}
