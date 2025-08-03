#include "game/draw.hh"
#include "game/world.hh"
#include "raylib.h"

void yumeami::draw_world(World &world, RenderTexture &viewport) {
  update_camera(world, viewport);
  BeginMode2D(world.camera);

  // will add more in the future

  EndMode2D();
}
