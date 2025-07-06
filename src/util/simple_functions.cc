#include "util/simple_functions.hh"
#include "game/component/simple_components.hh"
#include "util/simple_types.hh"

yumeami::FloatTilePosition
yumeami::calculate_float_position_from_facing(const comp::Facing& facing,
                                              const FloatTilePosition& position)
{
  float x, y;

  switch (facing.direction) {

    case Direction4::DOWN:
      x = (float)position.x;
      y = (float)(position.y + 1);
      break;

    case Direction4::UP:
      x = (float)position.x;
      y = (float)(position.y - 1);
      break;

    case Direction4::LEFT:
      x = (float)(position.x - 1);
      y = (float)position.y;
      break;

    case Direction4::RIGHT:
      x = (float)(position.x + 1);
      y = (float)position.y;
      break;
  }

  return { .x = x, .y = y };
}

yumeami::IntTilePosition
yumeami::calculate_int_position_from_facing(const comp::Facing& facing,
                                            const IntTilePosition& position)
{
  int x, y;

  switch (facing.direction) {

    case Direction4::DOWN:
      x = position.x;
      y = position.y + 1;
      break;

    case Direction4::UP:
      x = position.x;
      y = position.y - 1;
      break;

    case Direction4::LEFT:
      x = position.x - 1;
      y = position.y;
      break;

    case Direction4::RIGHT:
      x = position.x + 1;
      y = position.y;
      break;
  }

  return { .x = x, .y = y };
}
