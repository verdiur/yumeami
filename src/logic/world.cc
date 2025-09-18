#include "logic/world.hh"
#include "logic/components.hh"


yumeami::World yumeami::create_world(const World::Config &config,
                                     const World::Resources &resources) {
  return World{
      .config = config,
      .resources = resources,
      .state = {.reg = {},
                .collision = Grid<int>(config.width, config.height, 0),
                .cam = {}},
  };
}


void yumeami::setup_world_collision(World &world) {
  auto view = world.state.reg.view<CollisionTag, TruePos>();
  for (auto [ent, true_pos] : view.each()) {
    world.state.collision.at(true_pos.x, true_pos.y) += 1;
  }
}
