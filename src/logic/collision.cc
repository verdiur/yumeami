#include "logic/collision.hh"
#include "spdlog/spdlog.h"


void yumeami::setup_update_collision_event_dispatcher(
    entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher.sink<UpdateCollisionEvent>()
            .connect<&handle_update_collision_event>();
  // clang-format on
}


void yumeami::handle_update_collision_event(const UpdateCollisionEvent &event) {
  WorldState &wstate = event.world->state;
  TruePos src = event.src;
  TruePos dst = event.dst;

  if (src.x < 0 || src.x >= wstate.collision.get_width() || src.y < 0 ||
      src.y >= wstate.collision.get_height()) {
    spdlog::error(
        "[UpdateCollisionEvent] src position out of bounds. Event is ignored");
    return;
  }
  if (dst.x < 0 || dst.x >= wstate.collision.get_width() || dst.y < 0 ||
      dst.y >= wstate.collision.get_height()) {
    spdlog::error(
        "[UpdateCollisionEvent] dst position out of bounds. Event is ignored");
    return;
  }

  int &src_val = wstate.collision.at(src.x, src.y);
  int &dst_val = wstate.collision.at(dst.x, dst.y);

  if (src_val < 0) {
    spdlog::error("[UpdateCollisionEvent] src value is negative");
    return;
  }
  if (dst_val < 0) {
    spdlog::error("[UpdateCollisionEvent] dst value is negative");
    return;
  }

  src_val--;
  dst_val++;
}
