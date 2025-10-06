#include "_sandbox/decl.hh"
#include "ai/idle.hh"
#include "ai/move_random.hh"
#include "logic/components.hh"
#include "logic/movement.hh"
#include "logic/world.hh"
#include "logic/zsort.hh"
#include "resman/texture.hh"
#include <memory>


yumeami::World
yumeami::sandbox::create_background_world(SheetCache &sheet_cache,
                                          TextureCache &tex_cache) {
  if (!sheet_cache.load(1, {"resources/pnj.png", 16, 16}))
    throw std::runtime_error("spritesheet loading failed");
  Sheet *sheet = sheet_cache.get(1);

  if (!tex_cache.load(1, {"resources/Candle3.png"}))
    throw std::runtime_error("texture loading failed");

  World world = create_world(
      {
          .width = 40,
          .height = 40,
          .tile_size = 16,
          .wrap = false,
          .clamp_camera = false,
      },
      {.sheet_ids = {}});
  WorldState &wstate = world.state;

  entt::entity rm = wstate.reg.create();
  wstate.reg.emplace<DrawPos>(rm, 0, 0);
  wstate.reg.emplace<Sprite>(rm, 1, 0, 0);
  wstate.reg.emplace<TruePos>(rm, 0, 0);
  wstate.reg.emplace<MovementState>(rm);
  wstate.reg.emplace<Velocity>(rm, 0.4f);
  wstate.reg.emplace<CameraTargetTag>(rm);
  emplace_zsort(wstate.reg, rm);

  auto &actions = wstate.reg.emplace<ActionState>(rm);
  actions.possible[IdleAction::name()] =
      std::make_unique<IdleAction>(IdleAction{rm});
  actions.possible[RandomMoveAction::name()] =
      std::make_unique<RandomMoveAction>(RandomMoveAction{rm});

  // entt::entity cam_target = wstate.reg.create();
  // wstate.reg.emplace<DrawPos>(cam_target, 0, 0);
  // wstate.reg.emplace<CameraTargetTag>(cam_target);

  entt::entity bg = wstate.reg.create();
  wstate.reg.emplace<Background>(bg, 1, 0, 0);
  wstate.reg.emplace<SpritePixelPos>(bg, 100, 100);

  return world;
}
