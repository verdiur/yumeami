#include "logic/decision.hh"
#include <algorithm>


void yumeami::update_best_action(PossibleActions &actions, World &world) {
  for (auto &[_, action] : actions.possible) {
    action->set_score(world);
  }

  auto it = std::ranges::max_element(
      actions.possible, [](const auto &lhs, const auto &rhs) {
        return lhs.second->score > rhs.second->score;
      });

  actions.best = it->second.get();
}
