#include "game/system/update_movement.hh"
#include "game/component/movement_state.hh"

namespace yumeami::s {
namespace impl {

  void run_movement_state_machine(c::MovementState& state)
  {
    // TODO:
  }

} // namespace impl

void
update_movement(entt::registry& registry)
{
  auto view = registry.view<c::MovementState>();
  for (auto [entity, state] : view->each()) {
    // run state machine...
    // TODO: implement state machine
  }
}

} // namespace yumeami::s
