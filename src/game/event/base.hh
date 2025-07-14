#pragma once
#include <concepts>
#include <optional>
#include <queue>

namespace yumeami::event {

  /**
   * @class Event
   * @brief Base Event class. All event classes must derive from it.
   *
   */
  struct Event
  {};

  /**
   * @brief EventType must be a derived class of Event
   *
   * @tparam EventType
   */
  template<class EventType>
  concept EventDerived = std::derived_from<EventType, Event>;

  /**
   * @brief Base Queue class
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
     * @brief Consume an event from the queue.
     * The event will be popped out, and then copy-returned.
     *
     * @return Consumed event
     */
    std::optional<EventType> consume()
    {
      if (queue.empty()) {
        return std::nullopt;
      }
      EventType event = queue.front();
      queue.pop();
      return std::optional<EventType>{ event };
    }

  private:
    std::queue<EventType> queue;
  };

} // namespace yumeami::event
