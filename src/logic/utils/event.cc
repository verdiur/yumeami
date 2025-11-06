#include "logic/utils/event.hh"
#include "model/world/world.hh"
#include "spdlog/spdlog.h"
#include <string_view>


bool yumeami::event_entity_exists(World *world, const entt::entity ent,
                                  const std::string_view log_prefix) {
  bool val = world->state.registry.valid(ent);
  if (!val) {
    spdlog::warn("[{}] entity not found", log_prefix);
  }
  return val;
}
