#include "logic/animation.hh"
#include "logic/components.hh"
#include "logic/event_op.hh"
#include "logic/world.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <stdexcept>


void yumeami::setup_animation_event_dispatcher(entt::dispatcher &dispatcher) {
  // clang-format off
  dispatcher
    .sink<AnimationStartEvent>()
    .connect<&handle_animation_start_event>();
  dispatcher
    .sink<AnimationStopEvent>()
    .connect<&handle_animation_stop_event>();
  dispatcher
    .sink<AnimationStopEvent>()
    .connect<&handle_animation_fps_event>();
  dispatcher
    .sink<AnimationSwitchEvent>()
    .connect<&handle_animation_switch_event>();
  // clang-format on
}


void yumeami::handle_animation_start_event(const AnimationStartEvent &event) {
  if (!check_world_pointer(event.world))
    return;

  WorldState &wstate = event.world->state;
  auto anim_state = wstate.reg.try_get<AnimationState>(event.target);
  if (!anim_state) {
    spdlog::warn(
        "[AnimationStartEvent] target does not have required components");
    return;
  }

  if (event.reset)
    anim_state->frame = 0;

  anim_state->on = true;
}


void yumeami::handle_animation_stop_event(const AnimationStopEvent &event) {
  if (!check_world_pointer(event.world))
    return;

  WorldState &wstate = event.world->state;
  auto anim_state = wstate.reg.try_get<AnimationState>(event.target);
  if (!anim_state) {
    spdlog::warn(
        "[AnimationStopEvent] target does not have required components");
    return;
  }

  anim_state->on = false;
}


void yumeami::handle_animation_fps_event(const AnimationFpsEvent &event) {
  if (!check_world_pointer(event.world))
    return;

  WorldState &wstate = event.world->state;
  auto anim_state = wstate.reg.try_get<AnimationState>(event.target);
  if (!anim_state) {
    spdlog::warn(
        "[AnimationFpsEvent] target does not have required components");
    return;
  }

  anim_state->fps = event.fps;
}


void yumeami::handle_animation_switch_event(const AnimationSwitchEvent &event) {
  if (!check_world_pointer(event.world))
    return;

  WorldState &wstate = event.world->state;
  auto anim_state = wstate.reg.try_get<AnimationState>(event.target);
  if (!anim_state) {
    spdlog::warn(
        "[AnimationSwitchEvent] target does not have required components");
    return;
  }

  anim_state->current = event.current;
  if (event.reset)
    anim_state->frame = 0;
}


void yumeami::update_animation_state(World &world,
                                     entt::dispatcher &dispatcher) {
  WorldState &wstate = world.state;
  auto view = wstate.reg.view<AnimationState, Sprite>();
  for (auto [ent, state, sprite] : view.each()) {
    if (!state.on)
      continue;

    state.frame_progress += state.fps * GetFrameTime();
    if (state.frame_progress >= 1) {
      try {
        Animation &animation = state.map.at(state.current);
        state.frame = (state.frame + 1) % animation.length;
        sprite.row = animation.row;
        sprite.col = state.frame;

      } catch (std::out_of_range err) {
        spdlog::error("[Animation] animation name {} not found", state.current);
      }
    }
  }
}
