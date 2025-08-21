#include "game/world.hh"
#include "game/components.hh"
#include "raylib.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>


int yumeami::calc_px_tile_size(const World &world) {
  return world.tile_size * world.spx_multiplier;
}


/* IMPL *********************************************************************************/


void yumeami::impl::update_camera_target(World &world) {
  // camera should target player
  auto view = world.registry.view<PlayerTag, DrawTilePos>();
  for (auto [entity, draw_pos] : view.each()) {
    world.camera.target =
        Vector2{roundf(static_cast<float>((draw_pos.x + 1) * calc_px_tile_size(world))),
                roundf(static_cast<float>((draw_pos.y + 1) * calc_px_tile_size(world)))};
  }

  world.desired_camera_target = world.camera.target;
}


void yumeami::impl::update_camera_bounds(World &world, RenderTexture &viewport) {
  const float bound_x = world.width * calc_px_tile_size(world);
  const float bound_y = world.height * calc_px_tile_size(world);

  float half_screen_width = viewport.texture.width / (2.0f * world.camera.zoom);
  float half_screen_height = viewport.texture.height / (2.0f * world.camera.zoom);

  // clamp target
  world.camera.target.x = std::clamp(world.desired_camera_target.x, half_screen_width,
                                     bound_x - half_screen_width);
  world.camera.target.y = std::clamp(world.desired_camera_target.y, half_screen_height,
                                     bound_y - half_screen_height);
}


/* PUBLIC *******************************************************************************/


yumeami::World yumeami::create_world(tile_int width, tile_int height, spx_int tile_size,
                                     int spx_multiplier) {
  return World{
      .width = width,
      .height = height,
      .tile_size = tile_size,
      .spx_multiplier = spx_multiplier,
      .collision = Collision{.static_grid = std::vector<std::vector<int>>(
                                 width, std::vector<int>(height, 0)),
                             .dynamic_grid{}},
  };
}

void yumeami::unload_world_textures(World &world) {
  for (std::shared_ptr<Spritesheet> sheet : world.spritesheets) {
    UnloadTexture(sheet->texture);
  }
}


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
