#include "ai/base.hh"
namespace yumeami {

  struct RandomMoveAction : Action {
    float probability;
    float weight;

    RandomMoveAction(entt::entity target, float probability = 0.2,
                     float weight = 0.25);

    static std::string name() { return "random_move"; }
    std::string to_string() override { return name(); }
    void set_score(World &world) override;
    void execute(World &world, entt::dispatcher &dispatcher) override;
  };

} // namespace yumeami
