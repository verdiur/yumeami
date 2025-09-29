#include "ai/idle.hh"
#include "ai/base.hh"


yumeami::IdleAction::IdleAction(entt::entity target, float weight)
    : weight(weight) {
  this->target = target;
}


void yumeami::IdleAction::set_score(World &world) {
  if (score != weight)
    score = weight;
}


void yumeami::IdleAction::execute(World &world, entt::dispatcher &dispatcher) {
  dispatcher.trigger(ActionFinishedEvent{
      .world = &world,
      .target = target,
  });
}
