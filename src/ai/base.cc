#include "ai/base.hh"
#include "logic/event_op.hh"
#include "raylib.h"
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
  void evaluate_actions(World &world, ActionState &action_state) {
    for (auto &[_, action] : action_state.possible) {
      action->set_score(world);
    }

    auto it = std::ranges::max_element(
        action_state.possible, [](const auto &lhs, const auto &rhs) {
          return lhs.second->score < rhs.second->score;
        });

    action_state.best = it->second.get();
  }


  void update_timeout_state(ActionState &action_state) {
    action_state.timeout_progress += GetFrameTime();

    if (action_state.timeout_progress >= action_state.timeout_duration) {
      action_state.timeout_progress = 0;
      action_state.timeout = false;
    }
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::setup_dispatcher_action(entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
    .sink<ActionFinishedEvent>()
    .connect<&handle_action_finished_event>();
  dispatcher
    .sink<ActionTimeoutEvent>()
    .connect<&handle_action_timeout_event>();
  // clang-format on
}


void yumeami::handle_action_finished_event(const ActionFinishedEvent &event) {
  if (!check_world_pointer(event.world) ||
      !check_dispatcher_pointer(event.dispatcher))
    return;
  WorldState &wstate = event.world->state;

  auto action_state = wstate.reg.try_get<ActionState>(event.target);
  if (!action_state) {
    spdlog::info("[ActionFinishedEvent] target does not have ActionState "
                 "component. This event will be ignored.");
    return;
  }

  action_state->busy = false;
  event.dispatcher->trigger(ActionTimeoutEvent{
      .world = event.world,
      .target = event.target,
  });
}


void yumeami::handle_action_timeout_event(const ActionTimeoutEvent &event) {
  if (!check_world_pointer(event.world))
    return;
  WorldState &wstate = event.world->state;

  auto action_state = wstate.reg.try_get<ActionState>(event.target);
  if (!action_state) {
    spdlog::info("[ActionFinishedEvent] target does not have ActionState "
                 "component. This event will be ignored.");
    return;
  }

  action_state->timeout = true;
}


void yumeami::update_actions(World &world, entt::dispatcher &dispatcher) {
  auto view = world.state.reg.view<ActionState>();
  for (auto [ent, state] : view.each()) {
    if (state.busy)
      continue;

    if (state.timeout) {
      update_timeout_state(state);
      continue;
    }

    evaluate_actions(world, state);
    Action *best = state.best;
    if (!best) {
      spdlog::error(
          "[ActionState] no best action found. No event will be fired");
      continue;
    }

    // order here matters, IdleAction immediately fires an ActionFinishedEvent.
    // busy cannot be set to true before execute because of instant actions
    // such as IdleAction.
    state.busy = true;
    best->execute(world, dispatcher);
    dispatcher.trigger(ActionBeginEvent{
        .world = &world,
        .sender = best->target,
    });
  }
}
