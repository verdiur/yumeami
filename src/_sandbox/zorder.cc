#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"


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
