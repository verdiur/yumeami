#include "game/world.hh"
#include "entt/entity/fwd.hpp"
#include "game/component/simple_components.hh"

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

  return world;
}
