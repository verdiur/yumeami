#include "render/core/tiled.hh"
#include "common/types/vector.hh"
#include "model/camera/camera.hh"


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  void draw_row_tx(const CameraBounds &cam_bounds, TexelVector2 spacing,
                   TexelVector2 offset,
                   std::function<void(TexelVector2)> &draw_func) {
    tx current_x_pos = offset.x;
    while ((float)current_x_pos >= (float)cam_bounds.left_x) {
      current_x_pos -= spacing.x;
    }

    while ((float)current_x_pos <= (float)cam_bounds.right_x) {
      draw_func({
          .x = current_x_pos,
          .y = offset.y,
      });
      current_x_pos += spacing.x;
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::draw_tiled_tx(const CameraBounds &cam_bounds,
                            TexelVector2 spacing, TexelVector2 offset,
                            std::function<void(TexelVector2)> draw_func) {
  tx current_y_pos = offset.y;
  while ((float)current_y_pos >= (float)cam_bounds.top_y) {
    current_y_pos -= spacing.y;
  }

  while ((float)current_y_pos <= (float)cam_bounds.bottom_y) {
    draw_row_tx(cam_bounds, spacing,
                {
                    .x = offset.x,
                    .y = current_y_pos,
                },
                draw_func);
    current_y_pos += spacing.y;
  }
}
