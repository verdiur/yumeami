#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"


yumeami::World yumeami::sandbox::create_clamp_world() {
  World world = create_world(
      {
          .width = 10,
          .height = 5,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = true,
      },
      {.sheet_ids = {}});
  WorldState &wstate = world.state;

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
