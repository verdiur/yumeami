#include "ai/move_random.hh"
#include "ai/base.hh"
#include "logic/movement.hh"
#include <random>


yumeami::RandomMoveAction::RandomMoveAction(entt::entity target,
                                            float probability, float weight)
    : probability(probability), weight(weight) {
  this->target = target;
}


void yumeami::RandomMoveAction::set_score(World &world) {
  std::uniform_real_distribution<float> dist(0, 1);
  score = (dist(world.state.rd) < probability) * weight;
  // score = 1;
}


void yumeami::RandomMoveAction::execute(World &world,
                                        entt::dispatcher &dispatcher) {
  std::uniform_int_distribution<int> dist(0, 3);
  Direction dir = (Direction)dist(world.state.rd);

  dispatcher.enqueue(MovementEvent{
      .world = &world,
      .dispatcher = &dispatcher,
      .target = target,
      .direction = dir,
  });
}
