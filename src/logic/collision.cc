#include "logic/collision.hh"
#include "spdlog/spdlog.h"


void yumeami::setup_update_collision_event_dispatcher(
    entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
      .sink<UpdateCollisionEvent>()
      .connect<&handle_update_collision_event>();
  // clang-format on
}


void yumeami::handle_update_collision_event(const UpdateCollisionEvent &event) {
  World *world = event.world;
  TruePos src = event.src;
  TruePos dst = event.dst;

  if (src.x < 0 || src.x > world->collision.get_width() || src.y < 0 ||
      src.y > world->collision.get_height()) {
    spdlog::warn(
        "[UpdateCollisionEvent] src position out of bounds. Event is ignored");
    return;
  }
  if (dst.x < 0 || dst.x > world->collision.get_width() || dst.y < 0 ||
      dst.y > world->collision.get_height()) {
    spdlog::warn(
        "[UpdateCollisionEvent] dst position out of bounds. Event is ignored");
    return;
  }

  int &src_val = world->collision.at(src.x, src.y);
  int &dst_val = world->collision.at(dst.x, dst.y);

  if (src_val < 0) {
    spdlog::warn("[UpdateCollisionEvent] src value cannot be negative. Event "
                 "is ignored");
    return;
  }
  if (dst_val < 0) {
    spdlog::warn("[UpdateCollisionEvent] dst value cannot be negative. Event "
                 "is ignored");
    return;
  }

  src_val--;
  dst_val++;
}
