#include "common/viewport_transform.hh"
#include "common/raii.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cmath>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  float calc_scale(const int vp_width, const int vp_height,
                   const ViewportTransform &transform) {
    float raw_scale = std::min((float)GetScreenWidth() / vp_width,
                               (float)GetScreenHeight() / vp_height);

    if (raw_scale >= 1) {
      return std::floor(raw_scale);
    } else {
      float denominator = std::ceil(1 / raw_scale);
      spdlog::info("{}", denominator);
      return 1 / denominator;
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::calc_viewport_transform(const SafeRenderTexture &vp,
                                      ViewportTransform &transform) {
  int vp_width = vp->texture.width;
  int vp_height = vp->texture.height;
  float scale = calc_scale(vp_width, vp_height, transform);

  transform.src = Rectangle{
      0,
      0,
      static_cast<float>(vp_width),
      -static_cast<float>(vp_height),
  };
  transform.dst = Rectangle{
      static_cast<float>(GetScreenWidth() - vp_width * scale) / 2,
      static_cast<float>(GetScreenHeight() - vp_height * scale) / 2,
      static_cast<float>(vp_width * scale),
      static_cast<float>(vp_height * scale),
  };
}


void yumeami::draw_viewport(const SafeRenderTexture &vp,
                            const ViewportTransform &transform) {
  DrawTexturePro(vp->texture, transform.src, transform.dst, {}, 0, WHITE);
}
