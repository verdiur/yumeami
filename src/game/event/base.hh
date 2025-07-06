#pragma once
#include <concepts>

namespace yumeami::event {

  /**
   * @class Event
   * @brief Base Event class. All event classes must derive from it.
   *
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
   * @brief Listener class.
   * Receives events and updates its arguments accordingly.
   * To be used as component.
   *
   * @tparam EventType
   * @param event
   */
  template<EventDerived EventType>
  struct Listener
  {
    virtual void receive(const EventType& event);
  };

} // namespace yumeami::event
