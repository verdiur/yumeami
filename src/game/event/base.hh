#pragma once
#include "entt/entt.hpp"
#include <concepts>
#include <optional>
#include <queue>

namespace yumeami {

  /**
   * @class Event
   * @brief Base Event class. All event classes must derive from it.
   *
   */
  struct Event
  {
    entt::entity target_entity;
  };

  /**
   * @brief EventType must be a derived class of Event
   *
   * @tparam EventType
   */
  template<class EventType>
  concept EventDerived = std::derived_from<EventType, Event>;

  /**
   * @brief Base Queue class. Each entity has its own queues.
   * This class is not to be used by itself; technically you could use it as a component
   * but it's preferrable to derive it in another specialized class instead.
   *
   * @tparam EventType
   */
  template<EventDerived EventType>
  class EventQueue
  {
  public:
    const std::queue<EventType>& get_queue() const
    {
      return queue;
    }

    void clear()
    {
      std::queue<EventType>().swap(queue);
    }

    /**
     * @brief Receive an event and queue it.
     *
     * @param event Received event
     */
    void receive(const EventType& event)
    {
      queue.push(event);
    }

    /**
     * @brief Consume events from the queue, until it finds an event that targets the
     * specified entity.
     * The consumed events will be popped out. If a suitable event is found, it is
     * copy-returned.
     *
     * @param entity Entity that consumes the event
     * @return Consumed event
     */
    std::optional<EventType> consume(entt::entity entity)
    {
      while (!queue.empty()) {
        EventType event = queue.front();
        queue.pop();

        if (event.target_entity == entity) {
          return std::optional<EventType>{ event };
        }
      }
      // entire queue has been consumed
      return std::nullopt;
    }

  private:
    std::queue<EventType> queue;
  };

} // namespace yumeami
