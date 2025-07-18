#include "game/world.hh"
#include "entt/entity/fwd.hpp"
#include "game/event/simple_queues.hh"
#include "game/simple_components.hh"
#include "game/system/movement.hh"

yumeami::World
yumeami::create_dummy_world()
{
  World world = {};

  for (int i = 0; i < 15; i++) {
    entt::entity e = world.registry.create();

    auto& true_pos = world.registry.emplace<comp::TrueTilePosition>(e, i, i);
    auto& draw_pos =
      world.registry.emplace<comp::DrawTilePosition>(e, (float)i, (float)i);
    auto& sort_key = world.registry.emplace<comp::DrawSortKey>(e, &draw_pos);
  }

  entt::entity player = world.registry.create();
  auto& true_pos = world.registry.emplace<comp::TrueTilePosition>(player, 0, 1);
  auto& draw_pos =
    world.registry.emplace<comp::DrawTilePosition>(player, (float)0, (float)1);
  auto& sort_key = world.registry.emplace<comp::DrawSortKey>(player, &draw_pos);
  world.registry.emplace<comp::Movement>(player);
  world.registry.emplace<comp::Facing>(player);
  world.registry.emplace<comp::Velocity>(player, (float)0.25);
  world.registry.emplace<comp::MoveEventQueue>(player);
  world.registry.emplace<comp::ControllableFlag>(player);

  return world;
}
