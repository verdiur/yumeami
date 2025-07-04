#include "util/simple_functions.hh"
#include "util/simple_types.hh"

yumeami::FloatTilePosition
yumeami::calculate_facing_float_position(const comp::Facing& facing,
                                         const comp::TrueTilePosition& position)
{
  float x, y;

  switch (facing.direction) {

    case Direction4::BOTTOM:
      x = (float)position.x;
      y = (float)(position.y + 1);

    case Direction4::TOP:
      x = (float)position.x;
      y = (float)(position.y - 1);

    case Direction4::LEFT:
      x = (float)(position.x - 1);
      y = (float)position.y;

    case Direction4::RIGHT:
      x = (float)(position.x + 1);
      y = (float)position.y;
  }

  return { .x = x, .y = y };
}

yumeami::IntTilePosition
yumeami::calculate_facing_int_position(const comp::Facing& facing,
                                       const comp::TrueTilePosition& position)
{
  int x, y;

  switch (facing.direction) {

    case Direction4::BOTTOM:
      x = position.x;
      y = position.y + 1;

    case Direction4::TOP:
      x = position.x;
      y = position.y - 1;

    case Direction4::LEFT:
      x = position.x - 1;
      y = position.y;

    case Direction4::RIGHT:
      x = position.x + 1;
      y = position.y;
  }

  return { .x = x, .y = y };
}
