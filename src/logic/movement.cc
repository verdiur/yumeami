#include "logic/movement.hh"
#include "common/direction.hh"
#include "entt/entt.hpp"
#include "logic/components.hh"
#include "logic/components_op.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <cmath>


/* IMPL ***********************************************************************/


bool yumeami::impl::movement_target_exists(const World &world,
                                           entt::entity target) {
  return world.reg.valid(target);
}


bool yumeami::impl::movement_components_exist(
    const TruePos *tgt_true_pos, const DrawPos *tgt_draw_pos,
    const MovementState *tgt_mvt_state, const Velocity *tgt_velocity) {
  return (tgt_true_pos && tgt_draw_pos && tgt_mvt_state && tgt_velocity);
}


bool yumeami::impl::movement_facing_exists(const Facing *tgt_facing) {
  return tgt_facing;
}


bool yumeami::impl::movement_collides(const World &world, entt::entity target) {
  // TODO: implement when collision structure is decided on
  return true;
}


void yumeami::impl::movement_trigger(entt::entity target,
                                     const Direction &event_dir,
                                     TruePos &tgt_true_pos,
                                     MovementState &tgt_mvt_state) {
  tgt_mvt_state.src = tgt_true_pos;
  tgt_mvt_state.dst = direction_to_true_pos(tgt_true_pos, event_dir);
  tgt_mvt_state.moving = true;
  tgt_mvt_state.progress = 0;

  // advance true pos to the destination before animation begins.
  tgt_true_pos = tgt_mvt_state.dst;
}


/* PUBL ***********************************************************************/


void yumeami::setup_movement_event_dispatcher(entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
    .sink<MovementEvent>()
    .connect<&handle_movement_event>();
  // clang-format on
}


void yumeami::handle_movement_event(const MovementEvent &event) {
  World &world = *event.world;
  entt::entity target = event.target;
  Direction direction = event.direction;

  if (!impl::movement_target_exists(*event.world, event.target)) {
    spdlog::warn("handle_movement_event - target not found");
    return;
  }

  auto tgt_true_pos = world.reg.try_get<TruePos>(target);
  auto tgt_draw_pos = world.reg.try_get<DrawPos>(target);
  auto tgt_mvt_state = world.reg.try_get<MovementState>(target);
  auto tgt_facing = world.reg.try_get<Facing>(target);
  auto tgt_velocity = world.reg.try_get<Velocity>(target);

  if (!impl::movement_components_exist(tgt_true_pos, tgt_draw_pos,
                                       tgt_mvt_state, tgt_velocity)) {
    spdlog::warn("handle_movement_event - target doesn't have components");
    return;
  }

  if (tgt_mvt_state->moving) {
    return;
  }

  if (impl::movement_facing_exists(tgt_facing)) { // update facing if possible
    tgt_facing->dir = direction;
  }

  // TODO: check collision/wrap/oob

  impl::movement_trigger(target, direction, *tgt_true_pos, *tgt_mvt_state);
}


void yumeami::update_movement_state(World &world) {
  auto view = world.reg.view<TruePos, DrawPos, MovementState, Velocity>();
  for (auto [ent, true_pos, draw_pos, mvt_state, velocity] : view.each()) {

    if (mvt_state.moving) {
      mvt_state.progress += (1 / velocity) * GetFrameTime();
      draw_pos = {
          .x = std::lerp(mvt_state.src.x, mvt_state.dst.x, mvt_state.progress),
          .y = std::lerp(mvt_state.src.y, mvt_state.dst.y, mvt_state.progress),
      };

      if (mvt_state.progress >= 1) {
        mvt_state.moving = false;
        mvt_state.progress = 0;
        draw_pos = to_draw_pos(true_pos); // snap draw_pos
      }
    }
  }
}
