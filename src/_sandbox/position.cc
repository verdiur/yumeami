#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"


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
