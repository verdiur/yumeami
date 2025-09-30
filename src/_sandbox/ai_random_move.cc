#include "_sandbox/decl.hh"
#include "ai/idle.hh"
#include "ai/move_random.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include <memory>

yumeami::World yumeami::sandbox::create_random_move_world(SheetCache &cache) {
  if (!cache.load(1, {"resources/pnj.png", 16, 16}))
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
      {.sheet_ids = {}});
  WorldState &wstate = world.state;

  entt::entity rm = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(rm, 7, 7);
  wstate.reg.emplace<Sprite>(rm, 1, 0, 0);
  wstate.reg.emplace<TruePos>(rm, 7, 7);
  wstate.reg.emplace<MovementState>(rm);
  wstate.reg.emplace<Velocity>(rm, 0.4f);
  emplace_zsort(wstate.reg, rm);

  auto &actions = wstate.reg.emplace<ActionState>(rm);
  actions.possible[IdleAction::name()] =
      std::make_unique<IdleAction>(IdleAction{rm});
  actions.possible[RandomMoveAction::name()] =
      std::make_unique<RandomMoveAction>(RandomMoveAction{rm, 0.01});

  entt::entity cam_target = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(cam_target, 0, 0);
  wstate.reg.emplace<CameraTargetTag>(cam_target);

  return world;
}
