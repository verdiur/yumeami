#include "ai/base.hh"
#include "logic/event_op.hh"
#include "spdlog/spdlog.h"
#include <algorithm>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  /**
   * @brief Calculate score of each possible action for a single component, and
   * update the best action pointer accordingly.
   *
   * @param actions
   * @param world
   */
  void evaluate_actions(ActionState &action_state, World &world) {
    for (auto &[_, action] : action_state.possible) {
      action->set_score(world);
    }

    auto it = std::ranges::max_element(
        action_state.possible, [](const auto &lhs, const auto &rhs) {
          return lhs.second->score < rhs.second->score;
        });

    action_state.best = it->second.get();
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::setup_action_finished_event_dispatcher(
    entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
    .sink<ActionFinishedEvent>()
    .connect<&handle_action_finished_event>();
  // clang-format on
}


void yumeami::handle_action_finished_event(const ActionFinishedEvent &event) {
  if (!check_world_pointer(event.world))
    return;

  WorldState &wstate = event.world->state;

  auto action_state = wstate.reg.try_get<ActionState>(event.target);
  if (!action_state) {
    spdlog::info("[ActionFinishedEvent] target does not have ActionState "
                 "component. This event will be ignored.");
    return;
  }

  action_state->busy = false;
}


void yumeami::update_actions(World &world, entt::dispatcher &dispatcher) {
  auto view = world.state.reg.view<ActionState>();
  for (auto [entity, action_state] : view.each()) {
    if (action_state.busy)
      continue;

    evaluate_actions(action_state, world);
    Action *best = action_state.best;
    if (!best) {
      spdlog::error(
          "[ActionState] no best action found. No event will be fired");
      continue;
    }

    // order here matters, IdleAction immediately fires an ActionFinishedEvent.
    // occupied cannot be set to true before execute because of instant actions
    // such as IdleAction.
    action_state.busy = true;
    dispatcher.trigger(ActionBeginEvent{
        .world = &world,
        .sender = best->target,
    });
    best->execute(world, dispatcher);
  }
}
