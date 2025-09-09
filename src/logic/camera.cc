#include "logic/camera.hh"
#include "common/raii.hh"
#include "logic/components.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <cassert>


void yumeami::update_camera(World &world, const SafeRenderTex &vp, bool log) {
  auto view = world.reg.view<CameraTargetTag, DrawPos>();
  if (view.begin() == view.end()) {
    if (log)
      spdlog::warn("[Camera] no target found");
    return;
  }

  for (auto [entity, draw_pos] : view.each()) {
    // clang-format off
    float intended_target_x = floorf((draw_pos.x + 1) * world.tile_size * world.scale);
    float intended_target_y = floorf((draw_pos.y + 1) * world.tile_size * world.scale);
    // clang-format on

    // NOTE: as of now, clamp_camera being activated on a world smaller than the
    // viewport leads to the game crashing. The crash is caused by std::clamp
    // bounds failing assertions.
    if (world.clamp_camera) {
      // clang-format off
      float bound_x = world.width * world.tile_size * world.scale;
      float bound_y = world.height * world.tile_size * world.scale;

      float halfscr_width = vp->texture.width / (2.0 * world.cam.zoom);
      float halfscr_height = vp->texture.height / (2.0 * world.cam.zoom);
      float real_target_x = std::clamp(intended_target_x, halfscr_width, bound_x - halfscr_width);
      float real_target_y = std::clamp(intended_target_y, halfscr_height, bound_y - halfscr_height);
      // clang-format on

      world.cam.target = Vector2{
          .x = real_target_x,
          .y = real_target_y,
      };

    } else {
      world.cam.target = Vector2{
          .x = intended_target_x,
          .y = intended_target_y,
      };
    }

    break;
  }
}


void yumeami::setup_camera(World &world, const SafeRenderTex &vp) {
  // Camera2D fields are not initialized on construction for some reason beyond
  // my understanding. So we initialize them before updating the cam
  world.cam.zoom = 1;
  world.cam.rotation = 0;
  world.cam.offset = Vector2{
      .x = (float)vp->texture.width / world.scale,
      .y = (float)vp->texture.height / world.scale,
  };
  update_camera(world, vp, true);
}


yumeami::CameraBounds yumeami::get_camera_bounds(const World &world,
                                                 const SafeRenderTex &vp) {
  const Camera2D &cam = world.cam;
  float left = cam.target.x - cam.offset.x / cam.zoom;
  float top = cam.target.y - cam.offset.y / cam.zoom;
  float right = left + vp->texture.width / cam.zoom;
  float bottom = top + vp->texture.height / cam.zoom;

  return CameraBounds{left, right, top, bottom};
}
