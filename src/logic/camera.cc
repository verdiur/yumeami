#include "logic/camera.hh"
#include "common/raii.hh"
#include "logic/components.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <cassert>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  void update_camera_target(WorldState &wstate, const WorldConfig &wconfig,
                            const SafeRenderTex &vp, const DrawPos &draw_pos) {
    // clang-format off
    float intended_target_x = floorf((draw_pos.x + 0.5) * wconfig.tile_size * wconfig.scale);
    float intended_target_y = floorf((draw_pos.y + 0.5) * wconfig.tile_size * wconfig.scale);
    // clang-format on

    if (wconfig.clamp_camera) {

      float wwidth = wconfig.width * wconfig.tile_size * wconfig.scale;
      float wheight = wconfig.height * wconfig.tile_size * wconfig.scale;
      float halfscr_width = vp->texture.width / (2.0 * wstate.cam.zoom);
      float halfscr_height = vp->texture.height / (2.0 * wstate.cam.zoom);
      float real_target_y{};
      float real_target_x{};

      if (wwidth < vp->texture.width)
        real_target_x = wwidth / 2;
      else
        real_target_x = std::clamp(intended_target_x, halfscr_width,
                                   wwidth - halfscr_width);

      if (wheight < vp->texture.height)
        real_target_y = wheight / 2;
      else
        real_target_y = std::clamp(intended_target_y, halfscr_height,
                                   wheight - halfscr_height);

      wstate.cam.target = Vector2{
          .x = real_target_x,
          .y = real_target_y,
      };

    } else {
      wstate.cam.target = Vector2{
          .x = intended_target_x,
          .y = intended_target_y,
      };
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::update_camera(World &world, const SafeRenderTex &vp, bool log) {
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;
  auto view = wstate.reg.view<CameraTargetTag, DrawPos>();
  if (view.begin() == view.end()) {
    if (log)
      spdlog::warn("[Camera] no target found");
    return;
  }

  for (auto [entity, draw_pos] : view.each()) {
    update_camera_target(wstate, wconfig, vp, draw_pos);
    break;
  }
}


void yumeami::setup_camera(World &world, const SafeRenderTex &vp) {
  // Camera2D fields are not initialized on construction for some reason beyond
  // my understanding. So we initialize them before updating the cam
  const WorldConfig &wconfig = world.config;
  WorldState &wstate = world.state;

  wstate.cam.zoom = 1;
  wstate.cam.rotation = 0;
  wstate.cam.offset = Vector2{
      .x = (float)vp->texture.width / 2,
      .y = (float)vp->texture.height / 2,
  };
  update_camera(world, vp, true);
}


yumeami::CameraBounds yumeami::get_camera_bounds(const WorldState &wstate,
                                                 const SafeRenderTex &vp) {
  const Camera2D &cam = wstate.cam;
  float left = cam.target.x - cam.offset.x / cam.zoom;
  float top = cam.target.y - cam.offset.y / cam.zoom;
  float right = left + vp->texture.width / cam.zoom;
  float bottom = top + vp->texture.height / cam.zoom;
  float width = right - left;
  float height = bottom - top;

  return CameraBounds{left, right, top, bottom, width, height};
}
