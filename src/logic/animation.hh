#pragma once
#include "common/defines.hh"
#include "entt/entt.hpp"
#include "logic/world.hh"
#include <string>
namespace yumeami {

  struct Animation {
    int row;
    int length;
  };

  /**
   * @class AnimationState
   * @brief Component that holds the animation state of an entity
   *
   */
  struct AnimationState YUMEAMI_COMPONENT {
    std::map<std::string, Animation> map;
    bool on;
    std::string current;
    int frame = 0;
    float fps = 15;
    float frame_progress = 0;
  };

  struct AnimationStartEvent {
    World *world;
    entt::entity target;
    bool reset = true;
  };

  struct AnimationStopEvent {
    World *world;
    entt::entity target;
  };

  struct AnimationFpsEvent {
    World *world;
    entt::entity target;
    float fps;
  };

  struct AnimationSwitchEvent {
    World *world;
    entt::entity target;
    std::string current;
    bool reset = true;
  };

  /**
   * @brief Connect animation events to handler
   * @param dispatcher
   */
  void setup_dispatcher_animation(entt::dispatcher &dispatcher);

  /**
   * @brief Animation start event handler
   * @param event
   */
  void handle_animation_start_event(const AnimationStartEvent &event);

  /**
   * @brief Animation stop event handler
   * @param event
   */
  void handle_animation_stop_event(const AnimationStopEvent &event);

  /**
   * @brief Animation fps change handler
   * @param event
   */
  void handle_animation_fps_event(const AnimationFpsEvent &event);

  /**
   * @brief Animation switching handler
   * @param event
   */
  void handle_animation_switch_event(const AnimationSwitchEvent &event);


  /**
   * @brief Update the current animation state. Change sprite, advance frame if
   * necessary.
   *
   * @param world
   */
  void update_animation_state(World &world, entt::dispatcher &dispatcher);

} // namespace yumeami
