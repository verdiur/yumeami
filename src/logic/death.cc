#include "logic/death.hh"

void yumeami::DeathAction::set_score(World &world) {
  // NOTE: death is a priority action. When receiving a DeathEvent, an entity
  // sets the score of its DeathAction. This score is larger than 1, so it will
  // always take priority. It's kind of a hack but it works so
  score = 2;
}


void yumeami::DeathAction::execute(World &world, entt::dispatcher &dispatcher) {
  dispatcher.enqueue(DeathEvent{
      .world = &world,
      .target = target,
  });
}
