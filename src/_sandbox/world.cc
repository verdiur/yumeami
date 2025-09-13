#include "_sandbox/world.hh"
#include "entt/entity/fwd.hpp"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include <stdexcept>


yumeami::World yumeami::_sandbox::create_spritesheet_world(SheetPool &pool) {
  pool.load("test", "resources/test_sprsh.png", 16, 16);
  Sheet *sheet = pool.get("test");

  if (!sheet) {
    throw std::runtime_error("spritesheet loading failed");
  }

  World world = create_world(20, 15, 16, false, false, {"test"});

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = world.reg.create();
      world.reg.emplace<DrawPos>(e, c, r);
      world.reg.emplace<Sprite>(e, "test", r, c);
    }
  }

  entt::entity p = world.reg.create();
  world.reg.emplace<DrawPos>(p, 0, 0);
  world.reg.emplace<TruePos>(p, 0, 0);
  world.reg.emplace<MovementState>(p);
  world.reg.emplace<Velocity>(p, 0.4f);
  world.reg.emplace<PlayerTag>(p);
  world.reg.emplace<CameraTargetTag>(p);

  return world;
}


yumeami::World yumeami::_sandbox::create_wrap_world(SheetPool &pool) {
  pool.load("test", "resources/test_sprsh.png", 16, 16);
  Sheet *sheet = pool.get("test");

  if (!sheet) {
    throw std::runtime_error("spritesheet loading failed");
  }

  World world = create_world(21, 16, 16, true, false, {"test"});

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = world.reg.create();
      world.reg.emplace<DrawPos>(e, c, r);
      world.reg.emplace<Sprite>(e, "test", r, c);
    }
  }

  entt::entity p = world.reg.create();
  world.reg.emplace<DrawPos>(p, 0, 0);
  world.reg.emplace<TruePos>(p, 0, 0);
  world.reg.emplace<MovementState>(p);
  world.reg.emplace<Velocity>(p, 0.4f);
  world.reg.emplace<PlayerTag>(p);
  world.reg.emplace<CameraTargetTag>(p);

  return world;
}
