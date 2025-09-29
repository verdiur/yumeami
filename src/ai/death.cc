#include "ai/death.hh"
#include "ai/base.hh"
#include "entt/entt.hpp"
#include "logic/event_op.hh"


yumeami::DeathAction::DeathAction(entt::entity target) {
  this->target = target;
}


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


void yumeami::setup_death_event_dispatcher(entt::dispatcher &dispatcher) {
  dispatcher.sink<DeathEvent>().connect<&handle_death_event>();
}


void yumeami::handle_death_event(const DeathEvent &event) {
  if (!check_world_pointer(event.world))
    return;
  // trigger animation
  // and then die (when animation ends another event will be fired, and will
  // kill the entity for real)
}
