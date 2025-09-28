#pragma once
#include "entt/entt.hpp"
#include "logic/decision.hh"
#include "logic/world.hh"
namespace yumeami {

  struct DeathEvent {
    World *world;
    entt::entity target;
  };

  struct DeathAction : Action {
    std::string name() { return "death"; };

    void set_score(World &world);
    void execute(World &world, entt::dispatcher &dispatcher);
  };

} // namespace yumeami
