#include "logic/world.hh"
#include "logic/components.hh"


yumeami::World yumeami::create_world(tile width, tile height, spx tile_size,
                                     bool wrap, bool clamp_camera,
                                     std::vector<std::string> sheet_ids,
                                     int scale) {
  return World{
      .width = width,
      .height = height,
      .tile_size = tile_size,
      .wrap = wrap,
      .clamp_camera = clamp_camera,
      .scale = scale,
      .sheet_ids = sheet_ids,
      .reg = {},
      .collision = Grid<int>(width, height, 0),
      .cam = {},
  };
}


void yumeami::setup_world_collision(World &world) {
  auto view = world.reg.view<CollisionTag, TruePos>();
  for (auto [ent, true_pos] : view.each()) {
    world.collision.at(true_pos.x, true_pos.y) += 1;
  }
}


void yumeami::unload_world_registry(World &world) { world.reg.clear(); }
