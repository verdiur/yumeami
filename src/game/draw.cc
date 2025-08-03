#include "game/draw.hh"
#include "game/components.hh"
#include "game/world.hh"
#include "raylib.h"

void yumeami::draw_registry(entt::registry &registry, RenderTexture &viewport) {
  auto view = registry.view<DrawTilePos>();
  for (auto [entity, draw_pos] : view.each()) {
    // TODO:
  }
}

void yumeami::draw_world(World &world, RenderTexture &viewport) {
  update_camera(world, viewport);
  BeginMode2D(world.camera);

  draw_registry(world.registry, viewport);
  // will add more in the future...

  EndMode2D();
}
