#include "game/world.hh"
#include "entt/entity/fwd.hpp"
#include "game/components.hh"
#include "raylib.h"

namespace yumeami {

void
draw_world(World& world, RenderTexture& target)
{
  // sort registry
  world.registry.sort<c::DrawSortKey>(
    [](const c::DrawSortKey& lhs, const c::DrawSortKey& rhs) {
      return *(lhs.draw_tile_y) < *(rhs.draw_tile_y);
    });

  // the view must begin with the sort key, otherwise the order isn't retained
  auto view = world.registry.view<const c::DrawSortKey, const c::DrawTilePosition>();

  // begin drawing on target
  BeginTextureMode(target);
  ClearBackground(BLACK);

  for (auto [entity, sort_key, draw_pos] : view.each()) {
    DrawRectangleGradientV(draw_pos.x * world.tile_size * world.sprite_pixel_multiplier,
                           draw_pos.y * world.tile_size * world.sprite_pixel_multiplier,
                           world.tile_size * world.sprite_pixel_multiplier + 5,
                           world.tile_size * world.sprite_pixel_multiplier + 5,
                           BLUE,
                           GREEN);
  }

  // end drawing on target
  EndTextureMode();
}

World
create_dummy_world()
{
  World world = {};

  for (int i = 0; i < 15; i++) {
    entt::entity e = world.registry.create();

    auto& true_pos = world.registry.emplace<c::TrueTilePosition>(e, 0, i);
    auto& draw_pos = world.registry.emplace<c::DrawTilePosition>(e, (float)0, (float)i);
    auto& sort_key = world.registry.emplace<c::DrawSortKey>(e, &draw_pos.y);
  }

  return world;
}

} // namespace yumeami
