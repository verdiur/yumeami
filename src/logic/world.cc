#include "logic/world.hh"


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


void yumeami::unload_world_registry(World &world) { world.reg.clear(); }
