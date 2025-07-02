#include "game/world.hh"
#include "entt/entity/fwd.hpp"
#include "game/component/simple.hh"

namespace yumeami {

World
create_dummy_world()
{
  World world = {};

  for (int i = 0; i < 15; i++) {
    entt::entity e = world.registry.create();

    auto& true_pos = world.registry.emplace<c::TrueTilePosition>(e, i, i);
    auto& draw_pos = world.registry.emplace<c::DrawTilePosition>(e, (float)i, (float)i);
    auto& sort_key = world.registry.emplace<c::DrawSortKey>(e, &draw_pos);
  }

  return world;
}

} // namespace yumeami
