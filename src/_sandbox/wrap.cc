#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"


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
