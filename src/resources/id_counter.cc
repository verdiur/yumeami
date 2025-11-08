#include "resources/id_counter.hh"
#include "entt/core/fwd.hpp"


yumeami::IdCounter::IdCounter(entt::id_type initial_value)
    : counter(initial_value) {}


entt::id_type yumeami::IdCounter::next() {
  entt::id_type ret = counter;
  counter++;
  return ret;
}
