#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"


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
