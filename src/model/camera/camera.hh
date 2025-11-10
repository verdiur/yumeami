#pragma once
#include "common/units/px.hh"
#include "model/viewport/fwd.hh"
#include "model/world/fwd.hh"
namespace yumeami {

  struct CameraBounds {
    px left_x;
    px right_x;
    px top_y;
    px bottom_y;
    px width;
    px height;
    static CameraBounds create(const World &world, const Viewport &vp);
  };

} // namespace yumeami
