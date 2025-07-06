#pragma once
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "entt/signal/fwd.hpp"
#include "raylib.h"
#include <queue>

namespace yumeami {

  /**
   * @class KeyboardKeyEvent
   * @brief Event to dispatch when a key is pressed
   *
   */
  struct KeyboardKeyEvent
  {
    KeyboardKey key;
  };

  void dispatch_input_events(entt::dispatcher& dispatcher);

  namespace comp {

    /**
     * @class KeyboardKeyQueue
     * @brief Queue for KeyboardKey events.
     * To be used as a component.
     *
     */
    class KeyboardKeyQueue
    {
    public:
      const std::queue<KeyboardKey>& get_queue() const;

      /**
       * @brief Receive a KeyboardKeyEvent and queue it.
       *
       * @param event Received event
       */
      void receive(const KeyboardKeyEvent& event);

      /**
       * @brief Consume a key from the queue.
       * The key will be popped out, and then returned.
       * The queue must be non-empty.
       *
       * @return Consumed key
       */
      KeyboardKey consume();

      /**
       * @brief Clear queue.
       */
      void clear();

    private:
      std::queue<KeyboardKey> queue = {};
    };

  } // namespace comp

  namespace sys {

    /**
     * @brief Set up an event dispatcher for input events.
     * To be used when loading a world.
     *
     * @param dispatcher
     * @param registry
     */
    void initialize_input_event_dispatcher(entt::dispatcher& dispatcher,
                                           entt::registry& registry);
  } // namespace sys

} // namespace yumeami
