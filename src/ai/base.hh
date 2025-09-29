/**
 * @file base.hh
 * @brief Action-taking structs and functions. We use a utility AI pattern.
 *
 * @details
 * ## GLOBAL LOGIC FLOW
 *
 * At the start of each game loop iteration, all entities that have the
 * ActionState component calculates the scores of their possible actions.
 * The best action is then executed and the ActionState component is set as
 * "occupied". When the event handling is over (this can take multiple frames),
 * the system triggers an event back to the ActionState, signalling it that the
 * action is finished. ActionState is no longer marked as "occupied".
 *
 * ## WHERE IS EVERYTHING DEFINED ?
 *
 * The core, generic implementation is defined in this header + the
 * corresponding impl file. Specializations are in the library's other files.
 */

#pragma once
#include "entt/entt.hpp"
#include "logic/world.hh"
#include <string>
#include <unordered_map>
namespace yumeami {


  /**
   * @class Action
   * @brief Abstract generic action. Represents a possible action that an
   * entity can take.
   *
   * @details Executing an action does not necessarily mean actually performing
   * the thing described by the action. Preferably, the execute() method of the
   * derived actions should enqueue an event in the dispatcher. These events are
   * then processed separately.
   *
   * You might want to define a static name() function in derived classes for
   * the purpose of assigning a key to the action in a PossibleActions
   * component.
   *
   * You might also want to define a DerivedAction(entt::entity, ...)
   * constructor in derived classes.
   *
   * A derived class declaration might look like this:
   *
   *  @code{.cpp}
   *  struct DerivedAction : Action {
   *    // derived-specific members...
   *
   *    DerivedAction(entt::entity, \/\* derived-specific args... \*\/)
   *    static std::string name();
   *
   *    // virtual overrides...
   *  }
   *  @endcode
   *
   */
  struct Action {
    entt::entity target;
    float score = 0;

    virtual std::string to_string() { return "action"; }
    /**
     * @brief Calculates and sets score of Action. Default score calculation is
     * no-op
     * @param world
     */
    virtual void set_score(World &world) {}
    virtual void execute(World &world, entt::dispatcher &dispatcher) = 0;
  };


  /**
   * @class ActionBeginEvent
   * @brief Event that informs the system that the sender entity has begun an
   * action
   *
   */
  struct ActionBeginEvent {
    World *world;
    entt::entity sender;
  };


  /**
   * @class ActionFinishedEvent
   * @brief Event that informs a targeted entity that it has finished an action
   *
   */
  struct ActionFinishedEvent {
    World *world;
    entt::entity target;
  };


  /**
   * @class PossibleActions
   * @brief Component that stores all possible actions of an entity, and also
   * the current best action to take. The keys of the map are the name of the
   * corresponding actions.
   *
   */
  struct ActionState {
    // abstract classes can only be used in templates via a ref or pointer
    using Map = std::unordered_map<std::string, std::unique_ptr<Action>>;

    Map possible;
    Action *best = nullptr;
    bool occupied = false;

    // std::unique_ptr cannot be copied
    ActionState(const ActionState &other) = delete;
    ActionState &operator=(ActionState &other) = delete;

    // constructor
    ActionState() = default;
  };


  void setup_action_finished_event_dispatcher(entt::dispatcher &dispatcher);


  /**
   * @brief Action finishing event handler. Frees the occupied status of the
   * ActionState component, if it exists.
   *
   * @param event
   */
  void handle_action_finished_event(const ActionFinishedEvent &event);


  /**
   * @brief Evaluate and execute the best action for all applicable entities.
   * @param world
   * @param dispatcher
   */
  void update_actions(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
