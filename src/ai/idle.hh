#pragma once
#include "ai/base.hh"
#include "logic/world.hh"
#include <limits>
namespace yumeami {

  /**
   * @class IdleAction
   * @brief Action that does nothing. Its score will always be equal to its
   * weight, which is defined as epsilon by default: this effectively turns
   * IdleAction into a default action. The execute() method simply triggers an
   * ActionFinishedEvent targeting the entity itself.
   *
   */
  struct IdleAction : Action {
    float weight;

    IdleAction(entt::entity target,
               float weight = std::numeric_limits<float>::epsilon());

    static std::string name() { return "idle"; }
    std::string to_string() override { return name(); }
    void set_score(World &world) override;
    void execute(World &world, entt::dispatcher &dispatcher) override;
  };

} // namespace yumeami
