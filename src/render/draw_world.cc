#include "render/draw_world.hh"
#include "render/draw_sprites.hh"
#include "resman/texture.hh"


void yumeami::draw_world(World &world, SheetPool &pool) {
  draw_sprites(world, pool);
}
