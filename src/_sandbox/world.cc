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
  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {"test"},
      });
  WorldState &wstate = world.state;

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = wstate.reg.create();
      wstate.reg.emplace<DrawPos>(e, c, r);
      wstate.reg.emplace<Sprite>(e, "test", r, c);
    }
  }

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);

  return world;
}


yumeami::World yumeami::_sandbox::create_wrap_world(SheetPool &pool) {
  pool.load("test", "resources/test_sprsh.png", 16, 16);
  Sheet *sheet = pool.get("test");

  if (!sheet) {
    throw std::runtime_error("spritesheet loading failed");
  }

  // World world = create_world(21, 16, 16, true, false, {"test"});
  World world = create_world(
      {
          .width = 21,
          .height = 16,
          .tile_size = 16,
          .wrap = true,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {"test"},
      });
  WorldState &wstate = world.state;

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = wstate.reg.create();
      wstate.reg.emplace<DrawPos>(e, c, r);
      wstate.reg.emplace<Sprite>(e, "test", r, c);
    }
  }

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);

  return world;
}


yumeami::World yumeami::_sandbox::create_collision_world() {
  // World world = create_world(20, 15, 16, true, false);
  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = true,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {"test"},
      });
  WorldState &wstate = world.state;

  std::vector<TruePos> positions = {
      {19, 0}, {19, 1}, {19, 2}, {2, 2}, {2, 3}, {2, 4}, {3, 2},
  };
  for (TruePos pos : positions) {
    entt::entity e = wstate.reg.create();
    wstate.reg.emplace<TruePos>(e, pos.x, pos.y);
    wstate.reg.emplace<DrawPos>(e, pos.x, pos.y);
    wstate.reg.emplace<CollisionTag>(e);
  }

  entt::entity no_coll = wstate.reg.create();
  wstate.reg.emplace<TruePos>(no_coll, 10, 10);
  wstate.reg.emplace<DrawPos>(no_coll, 10, 10);

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);
  wstate.reg.emplace<CollisionTag>(p);
  wstate.reg.emplace<Facing>(p, Direction::DOWN);

  setup_world_collision(world);
  return world;
}
