#include "game/system/draw.hh"
#include "game/component/simple_components.hh"
#include "raylib.h"

void
yumeami::sys::draw_world(World& world, RenderTexture& target)
{
  // sort entities by draw order
  world.registry.sort<comp::DrawSortKey>(
    [](const comp::DrawSortKey& lhs, const comp::DrawSortKey& rhs) {
      return lhs.draw_tile_position->y < rhs.draw_tile_position->y;
    });

  // the view must begin with the sort key, otherwise the order isn't retained
  auto view =
    world.registry.view<const comp::DrawSortKey, const comp::DrawTilePosition>();

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
