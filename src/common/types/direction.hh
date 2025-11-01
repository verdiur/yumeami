#pragma once
#include <raylib.h>
#include <string>
namespace yumeami {

  enum struct Direction {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

  std::string direction_to_string(Direction dir);
  Vector2 direction_to_vector(Direction dir);

} // namespace yumeami
