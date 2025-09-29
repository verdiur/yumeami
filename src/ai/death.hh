/**
 * @file
 * @brief Death-related actions, updates and event handling. Most definitely the
 * jolliest files of this codebase.
 */

#pragma once
#include "ai/base.hh"
#include "entt/entt.hpp"
#include "logic/world.hh"
namespace yumeami {

  struct Health {
    enum struct State { ALIVE, DYING, DEAD } state = Health::State::ALIVE;
    int value;
  };

  struct DeathEvent {
    World *world;
    entt::entity target;
  };

  struct DeathAction : Action {
    DeathAction(entt::entity target);

    static std::string name() { return "death"; };
    std::string to_string() override { return name(); }
    void set_score(World &world) override;
    void execute(World &world, entt::dispatcher &dispatcher) override;
  };

  void setup_death_event_dispatcher(entt::dispatcher &dispatcher);

  void handle_death_event(const DeathEvent &event);

} // namespace yumeami
