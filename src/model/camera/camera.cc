#include "model/camera/camera.hh"
#include "common/raii/render_texture.hh"
#include "model/viewport/viewport.hh"
#include "model/world/world.hh"
#include <raylib.h>


yumeami::CameraBounds yumeami::CameraBounds::create(const World &world,
                                                    const Viewport &vp) {
  const Camera2D &cam = world.state.camera;
  SafeRenderTexture &rt = vp.render_texture;

  px left{cam.target.x - cam.offset.x / cam.zoom};
  px top{cam.target.y - cam.offset.y / cam.zoom};
  px right{(float)left + (float)rt->texture.width / cam.zoom};
  px bottom{(float)top + (float)rt->texture.height / cam.zoom};
  px width = (float)right - (float)left;
  px height = (float)bottom - (float)top;

  return CameraBounds{left, right, top, bottom, width, height};
}
