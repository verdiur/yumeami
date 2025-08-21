#include "game/movement.hh"
#include "entt/fwd.hpp"
#include "game/collision.hh"
#include "game/components.hh"
#include "game/conversions.hh"
#include "game/world.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <cmath>


/* IMPL *********************************************************************************/


bool yumeami::impl::move_event_destination_is_oob(const World &world,
                                                  const TrueTilePos &destination) {
  bool oob_horizontal = (destination.x < 0) || (destination.x >= world.width);
  bool oob_vertical = (destination.y < 0) || (destination.y >= world.height);
  return oob_horizontal || oob_vertical;
}


/* PUBLIC *******************************************************************************/


void yumeami::setup_dispatcher_movement(entt::dispatcher &dispatcher) {
  dispatcher.sink<MoveEvent>().connect<&handle_move_event>();
}


void yumeami::handle_move_event(const MoveEvent &event) {
  entt::registry &registry = event.world->registry;
  Collision &collision = event.world->collision;
  const entt::entity target = event.target;

  // check if event target exists
  if (!registry.valid(target)) {
    spdlog::warn("handle_move_event: target does not exist. This event will be ignored.");
    return;
  }

  // check if event target has components
  if (!registry.all_of<TrueTilePos, DrawTilePos, Velocity, Movement>(target)) {
    spdlog::warn("handle_move_event: target does not have necessary components. This "
                 "event will be ignored.");
    return;
  }

  // get components
  auto &movement = registry.get<Movement>(target);
  if (movement.is_moving) { // drop handling if target is already moving
    return;
  }
  auto &true_tile_pos = registry.get<TrueTilePos>(target);
  auto &draw_tile_pos = registry.get<DrawTilePos>(target);
  TrueTilePos movement_destination =
      calc_true_tile_pos_from_direction4(true_tile_pos, event.direction);

  // if entity has facing, update it
  if (registry.all_of<Facing>(target)) {
    auto &facing = registry.get<Facing>(target);
    facing.fac = event.direction;
  }

  // check OOB
  if (impl::move_event_destination_is_oob(*event.world, movement_destination)) {
    return;
  }

  // check collision
  // TODO: check dynamic collision as well
  if (collision.get_static_cell(movement_destination.x, movement_destination.y) > 0) {
    return;
  }

  // update positions and collision
  movement.from = true_tile_pos;
  movement.to = movement_destination;
  true_tile_pos = movement.to; // NOTE: true position is updated before movement begins
  update_static_collision(collision, movement.from, movement.to);

  // init movement
  movement.progress = 0;
  movement.is_moving = true;
}


void yumeami::update_movement(World &world) {
  auto view = world.registry.view<TrueTilePos, DrawTilePos, Velocity, Movement>();
  for (auto [entity, true_pos, draw_pos, velocity, movement] : view.each()) {

    if (movement.is_moving) {
      movement.progress += (1 / velocity.vel) * GetFrameTime();
      draw_pos.x = std::lerp(movement.from.x, movement.to.x, movement.progress);
      draw_pos.y = std::lerp(movement.from.y, movement.to.y, movement.progress);

      if (movement.progress >= 1) {
        draw_pos = to_draw_tile_pos(movement.to);
        movement.progress = 0;
        movement.is_moving = false;
      }
    }
  }
}
