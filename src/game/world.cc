#include "game/world.hh"
#include "game/components.hh"
#include "raylib.h"
#include <algorithm>

/* IMPL *********************************************************************************/

void yumeami::impl::update_camera_target(World &world) {
  // camera target
  auto view = world.registry.view<PlayerFlag, TrueTilePos>();
  for (auto [entity, true_pos] : view.each()) {
    world.camera.target =
        Vector2{static_cast<float>(true_pos.x), static_cast<float>(true_pos.y)};
  }
  // camera desired target
  world.desired_camera_target = world.camera.target;
}

void yumeami::impl::update_camera_bounds(World &world, RenderTexture &viewport) {
  // calc bounds
  const float bound_x = world.width * world.tile_size * world.spritepx_multiplier;
  const float bound_y = world.height * world.tile_size * world.spritepx_multiplier;
  // calc half camera screen width
  float half_screen_width = viewport.texture.width / (2.0f * world.camera.zoom);
  float half_screen_height = viewport.texture.height / (2.0f * world.camera.zoom);
  // clamp target
  world.camera.target.x = std::clamp(world.desired_camera_target.x, half_screen_width,
                                     bound_x - half_screen_width);
  world.camera.target.y = std::clamp(world.desired_camera_target.y, half_screen_height,
                                     bound_y - half_screen_height);
}

/* PUBLIC *******************************************************************************/

void yumeami::setup_camera(World &world, RenderTexture &viewport) {
  impl::update_camera_target(world);
  // camera offset
  world.camera.offset =
      Vector2{viewport.texture.width / 2.0f, viewport.texture.height / 2.0f};
  // also set other fields
  world.camera.zoom = 1.0f;
  world.camera.rotation = 0;
}

void yumeami::update_camera(World &world, RenderTexture &viewport) {
  impl::update_camera_target(world);
  impl::update_camera_bounds(world, viewport);
}
