#include "logic/collision/collision.hh"
#include "common/types/vector.hh"
#include "logic/movement/movement.hh"
#include "logic/utils/event.hh"
#include "model/world/world.hh"
#include "spdlog/spdlog.h"
#include <entt/signal/dispatcher.hpp>


/* IMPL ***********************************************************************/


namespace {
  using namespace yumeami;


  void on_entity_move_start_event(struct EntityMoveStartEvent &event) {
    event.dispatcher->trigger(UpdateCollisionCommand{
        event.world,
        event.dispatcher,
        event.src,
        event.dst,
    });
  }


} // namespace


/* PUBL ***********************************************************************/


void yumeami::setup_dispatcher_collision(entt::dispatcher &dispatcher) {
  // EntityMoveStartEvent triggers UpdateCollisionCommand
  dispatcher.sink<EntityMoveStartEvent>()
      .connect<&on_entity_move_start_event>();
  dispatcher.sink<UpdateCollisionCommand>()
      .connect<&handle_update_collision_command>();
}


void handle_update_collision_command(const UpdateCollisionCommand &cmd) {
  if (!is_event_valid(cmd)) return;

  WorldState &wstate = cmd.world->state;
  TileVector2 src = cmd.src;
  TileVector2 dst = cmd.dst;

  if ((int)src.x < 0 || (int)src.x >= wstate.collision.get_width() ||
      (int)src.y < 0 || (int)src.y >= wstate.collision.get_height()) {
    spdlog::error("[UpdateCollisionCommand] src position out of bounds. Event "
                  "is ignored");
    return;
  }
  if ((int)dst.x < 0 || (int)dst.x >= wstate.collision.get_width() ||
      (int)dst.y < 0 || (int)dst.y >= wstate.collision.get_height()) {
    spdlog::error("[UpdateCollisionCommand] dst position out of bounds. Event "
                  "is ignored");
    return;
  }

  int &src_val = wstate.collision.at((int)src.x, (int)src.y);
  int &dst_val = wstate.collision.at((int)dst.x, (int)dst.y);

  if (src_val < 0) {
    spdlog::error(
        "[UpdateCollisionCommand] src value is negative. Event is ignored");
    return;
  }
  if (dst_val < 0) {
    spdlog::error(
        "[UpdateCollisionCommand] dst value is negative. Event is ignored");
    return;
  }

  src_val--;
  dst_val++;
}
