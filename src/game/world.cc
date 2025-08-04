#include "game/world.hh"
#include "game/components.hh"
#include "game/movement.hh"
#include "raylib.h"
#include "util/direction.hh"
#include <algorithm>

/* IMPL *********************************************************************************/

void yumeami::impl::update_camera_target(World &world) {
  // camera should target player
  auto view = world.registry.view<PlayerFlag, TrueTilePos>();
  for (auto [entity, true_pos] : view.each()) {
    world.camera.target =
        Vector2{static_cast<float>(true_pos.x), static_cast<float>(true_pos.y)};
  }

  world.desired_camera_target = world.camera.target;
}

void yumeami::impl::update_camera_bounds(World &world, RenderTexture &viewport) {
  const float bound_x = world.width * world.tile_size * world.spritepx_multiplier;
  const float bound_y = world.height * world.tile_size * world.spritepx_multiplier;

  float half_screen_width = viewport.texture.width / (2.0f * world.camera.zoom);
  float half_screen_height = viewport.texture.height / (2.0f * world.camera.zoom);

  // clamp target
  world.camera.target.x = std::clamp(world.desired_camera_target.x, half_screen_width,
                                     bound_x - half_screen_width);
  world.camera.target.y = std::clamp(world.desired_camera_target.y, half_screen_height,
                                     bound_y - half_screen_height);
}

/* DEBUG ********************************************************************************/

yumeami::World yumeami::debug::create_dummy_world() {
  World world = {.width = 40, .height = 30};
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerFlag>(player);

  return world;
}

/* PUBLIC *******************************************************************************/

void yumeami::setup_camera(World &world, RenderTexture &viewport) {
  impl::update_camera_target(world);

  world.camera.offset =
      Vector2{viewport.texture.width / 2.0f, viewport.texture.height / 2.0f};
  world.camera.zoom = 1.0f;
  world.camera.rotation = 0;
}

void yumeami::update_camera(World &world, RenderTexture &viewport) {
  impl::update_camera_target(world);
  impl::update_camera_bounds(world, viewport);
}
