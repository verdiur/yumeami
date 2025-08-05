#include "game/debug.hh"
#include "game/components.hh"
#include "game/movement.hh"

yumeami::World yumeami::debug::create_player_test_world() {
  World world = {.width = 40, .height = 30};
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerTag>(player);

  return world;
}
