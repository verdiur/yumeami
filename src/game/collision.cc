#include "game/collision.hh"
#include "common/units.hh"
#include <cassert>


int yumeami::Collision::get_static_cell(tile_int x, tile_int y) const {
  assert(x >= 0);
  assert(y >= 0);
  return static_grid.at(x).at(y);
}


int &yumeami::Collision::get_static_cell(tile_int x, tile_int y) {
  assert(x >= 0);
  assert(y >= 0);
  return static_grid.at(x).at(y);
}


void yumeami::update_static_collision(Collision &collision, const TrueTilePos &from,
                                      const TrueTilePos &to) {
  assert(collision.get_static_cell(from.x, from.y) >= 0);
  collision.get_static_cell(from.x, from.y) -= 1;
  collision.get_static_cell(to.x, to.y) += 1;
}
