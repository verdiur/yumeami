#include "_sandbox/world.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include "resman/spritesheet.hh"
#include <stdexcept>


yumeami::World yumeami::sandbox::create_spritesheet_world(SheetCache &cache) {
  if (!cache.load(1, {"resources/test_sprsh.png", 16, 16}))
    throw std::runtime_error("spritesheet loading failed");
  Sheet *sheet = cache.get(1);

  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {1},
      });
  WorldState &wstate = world.state;

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = wstate.reg.create();
      wstate.reg.emplace<Sprite>(e, 1, r, c);
      wstate.reg.emplace<DrawPos>(e, c, r);
      wstate.reg.emplace<Elevation>(e, -1);
      emplace_zsort(wstate.reg, e);
    }
  }

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);
  emplace_zsort(wstate.reg, p);

  return world;
}


yumeami::World yumeami::sandbox::create_wrap_world(SheetCache &cache) {
  if (!cache.load(1, {"resources/test_sprsh.png", 16, 16}))
    throw std::runtime_error("spritesheet loading failed");
  Sheet *sheet = cache.get(1);

  World world = create_world(
      {
          .width = 21,
          .height = 16,
          .tile_size = 16,
          .wrap = true,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {1},
      });
  WorldState &wstate = world.state;

  for (int r = 0; r < sheet->rows; r++) {
    for (int c = 0; c < sheet->cols; c++) {
      entt::entity e = wstate.reg.create();
      wstate.reg.emplace<Sprite>(e, 1, r, c);
      wstate.reg.emplace<DrawPos>(e, c, r);
      wstate.reg.emplace<Elevation>(e, -1);
      emplace_zsort(wstate.reg, e);
    }
  }

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);
  emplace_zsort(wstate.reg, p);

  return world;
}


yumeami::World yumeami::sandbox::create_collision_world() {
  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = true,
          .clamp_camera = false,
      },
      {
          .sheet_ids = {},
      });
  WorldState &wstate = world.state;

  std::vector<TruePos> positions = {
      {19, 0}, {19, 1}, {19, 2}, {2, 2}, {2, 3}, {2, 4}, {3, 2},
  };
  for (TruePos pos : positions) {
    entt::entity e = wstate.reg.create();
    wstate.reg.emplace<TruePos>(e, pos.x, pos.y);
    wstate.reg.emplace<DrawPos>(e, pos.x, pos.y);
    wstate.reg.emplace<Elevation>(e, -1);
    wstate.reg.emplace<CollisionTag>(e);
    emplace_zsort(wstate.reg, e);
  }

  entt::entity no_coll = wstate.reg.create();
  wstate.reg.emplace<TruePos>(no_coll, 10, 10);
  wstate.reg.emplace<DrawPos>(no_coll, 10, 10);
  wstate.reg.emplace<Elevation>(no_coll, -1);
  emplace_zsort(wstate.reg, no_coll);

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);
  wstate.reg.emplace<CollisionTag>(p);
  wstate.reg.emplace<Facing>(p, Direction::DOWN);
  emplace_zsort(wstate.reg, p);

  setup_world_collision(world);
  return world;
}


yumeami::World
yumeami::sandbox::create_sprite_position_world(SheetCache &cache) {
  if (!cache.load(1, {"resources/test_sprsh.png", 20, 30}))
    throw std::runtime_error("spritesheet loading failed");
  Sheet *sheet = cache.get(1);

  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = true,
      },
      {
          .sheet_ids = {},
      });
  WorldState &wstate = world.state;

  std::vector<TruePos> positions = {{1, 1}, {3, 1}, {5, 3}};
  for (TruePos pos : positions) {
    entt::entity e = wstate.reg.create();
    wstate.reg.emplace<DrawPos>(e, pos.x, pos.y);
    wstate.reg.emplace<Sprite>(e, 1, 1, 1);
    wstate.reg.emplace<Elevation>(e, 1);
    emplace_zsort(wstate.reg, e);
  }

  entt::entity p = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(p, 0, 0);
  wstate.reg.emplace<TruePos>(p, 0, 0);
  wstate.reg.emplace<MovementState>(p);
  wstate.reg.emplace<Velocity>(p, 0.4f);
  wstate.reg.emplace<PlayerTag>(p);
  wstate.reg.emplace<CameraTargetTag>(p);
  emplace_zsort(wstate.reg, p);

  return world;
}


yumeami::World yumeami::sandbox::create_zorder_world(SheetCache &cache) {
  if (!cache.load(1, {"resources/test_layer.png", 16, 16}))
    throw std::runtime_error("spritesheet loading failed");
  Sheet *sheet = cache.get(1);

  World world = create_world(
      {
          .width = 20,
          .height = 15,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = true,
      },
      {.sheet_ids = {1}});
  WorldState &wstate = world.state;

  // entt::entity floor0 = wstate.reg.create();
  // wstate.reg.emplace<DrawPos>(floor0, 0, 0);
  // wstate.reg.emplace<Sprite>(floor0, 1, 0, 0);
  // wstate.reg.emplace<Elevation>(floor0, Elevation::Enum::NORMAL);
  // emplace_zorder(wstate, floor0);
  //
  // entt::entity floor1 = wstate.reg.create();
  // wstate.reg.emplace<DrawPos>(floor1, 0, 0);
  // wstate.reg.emplace<Sprite>(floor1, 1, 1, 0);
  // wstate.reg.emplace<Elevation>(floor1, Elevation::Enum::NORMAL);
  // wstate.reg.emplace<Floor>(floor1, 1);
  // emplace_zorder(wstate, floor1);

  entt::entity elev_above = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(elev_above, 1, 0);
  wstate.reg.emplace<Sprite>(elev_above, 1, 2, 0);
  wstate.reg.emplace<Elevation>(elev_above, 1);
  emplace_zsort(wstate.reg, elev_above);

  entt::entity elev_under = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(elev_under, 1, 0);
  wstate.reg.emplace<Sprite>(elev_under, 1, 2, 0);
  wstate.reg.emplace<Elevation>(elev_under, -1);
  emplace_zsort(wstate.reg, elev_under);

  entt::entity cam_target = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(cam_target, 0, 0);
  wstate.reg.emplace<CameraTargetTag>(cam_target);

  return world;
}
