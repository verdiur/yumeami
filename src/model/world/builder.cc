#include "model/world/builder.hh"
#include "common/grid/grid.hh"
#include "model/components/components.hh"
#include "model/world/world.hh"


yumeami::WorldBuilder::WorldBuilder(int width, int height) : world_() {
  world_->config.width = width;
  world_->config.height = height;

  // setup state
  world_->state.collision = Grid<int>(width, height, 0);
  world_->state.camera.offset = {}; // TODO: center target
  world_->state.camera.rotation = 0;
  world_->state.camera.target = {};
  world_->state.camera.zoom = 1;
}


yumeami::WorldBuilder &yumeami::WorldBuilder::build_config(tx tile_size,
                                                           bool wrap,
                                                           bool clamp_camera) {
  world_->config.tile_size = tile_size;
  world_->config.wrap = wrap;
  world_->config.clamp_camera = clamp_camera;
  return *this;
}


yumeami::WorldBuilder &yumeami::WorldBuilder::build_resources() {
  // TODO:
  return *this;
}


yumeami::World yumeami::WorldBuilder::world() { return std::move(*world_); }


void yumeami::setup_world_collision(World &world) {
  WorldState &wstate = world.state;
  auto view = wstate.registry.view<CollisionTag, TrueTilePos>();
  for (auto [ent, true_pos] : view.each()) {
    wstate.collision.at(true_pos.pos.x, true_pos.pos.y) += 1;
  }
}
