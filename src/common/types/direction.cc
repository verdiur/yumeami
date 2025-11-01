#include "common/types/direction.hh"
#include <raylib.h>
#include <stdexcept>
#include <string>


std::string yumeami::direction_to_string(Direction dir) {
  using enum Direction;
  switch (dir) {
  case NONE:
    return "NONE";
  case UP:
    return "UP";
  case DOWN:
    return "DOWN";
  case LEFT:
    return "LEFT";
  case RIGHT:
    return "RIGHT";
  }
  throw std::logic_error("Invalid conversion: Direction -> std::string");
}


Vector2 yumeami::direction_to_vector(Direction dir) {
  using enum Direction;
  switch (dir) {
  case NONE:
    return {};
  case UP:
    return {0, -1};
  case DOWN:
    return {0, 1};
  case LEFT:
    return {-1, 0};
  case RIGHT:
    return {1, 0};
  }
  throw std::logic_error("Invalid conversion: Direction -> Vector2");
}
