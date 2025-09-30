#include "logic/animation.hh"
#include "_sandbox/decl.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include "resman/spritesheet.hh"
#include <stdexcept>


yumeami::World
yumeami::sandbox::create_animation_world(yumeami::SheetCache &cache) {
  if (!cache.load(1, {"resources/test_anim.png", 16, 16}))
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

  for (int r = 0; r < 15; r++) {
    for (int c = 0; c < 20; c++) {
      entt::entity e = wstate.reg.create();
      wstate.reg.emplace<DrawPos>(e, c, r);
      wstate.reg.emplace<Sprite>(e, 1, 0, 0);
      emplace_zsort(wstate.reg, e);

      wstate.reg.emplace<AnimationState>(e,
                                         AnimationState::Map{
                                             {"one", Animation{0, 10}},
                                             {"two", Animation{1, 10}},
                                         },
                                         true, "one");
    }
  }

  entt::entity cam_target = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(cam_target, 0, 0);
  wstate.reg.emplace<CameraTargetTag>(cam_target);

  return world;
}
