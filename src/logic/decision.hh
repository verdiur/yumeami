/**
 * @file decision.hh
 * @brief Decision-taking structs and functions
 */

#pragma once
#include "entt/entt.hpp"
#include "entt/signal/fwd.hpp"
#include "logic/world.hh"
#include <string>
#include <unordered_map>
namespace yumeami {

  /**
   * @class Action
   * @brief Abstract generic action. Represents a possible action that an
   * entity can take.
   *
   */
  struct Action {
    entt::entity target;
    float score = 0;
    virtual std::string name() = 0;

    /**
     * @brief Calculates and sets score of Action. Default score calculation is
     * no-op
     * @param world
     */
    virtual void set_score(World &world) {}
    virtual void execute(World &world, entt::dispatcher &dispatcher) = 0;
  };

  /**
   * @class PossibleActions
   * @brief Component that stores all possible actions of an entity, and also
   * the current best action to take. The keys of the map are the name of the
   * corresponding actions.
   *
   */
  struct PossibleActions {
    std::unordered_map<std::string, std::unique_ptr<Action>> possible;
    Action *best = nullptr;
  };

  /**
   * @brief Calculate score of each possible action, and update the best action
   * pointer accordingly.
   *
   * @param actions
   * @param world
   */
  void update_best_action(PossibleActions &actions, World &world);

} // namespace yumeami
