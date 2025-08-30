#include "logic/components_op.hh"
#include "common/direction.hh"
#include "logic/components.hh"


yumeami::TruePos yumeami::to_true_pos(const DrawPos &draw_pos) {
  return TruePos{draw_pos.x, draw_pos.y};
}


yumeami::DrawPos yumeami::to_draw_pos(const TruePos &true_pos) {
  return DrawPos{true_pos.x, true_pos.y};
}


yumeami::TruePos yumeami::direction_to_true_pos(const TruePos &true_pos,
                                                const Direction &dir) {
  switch (dir) {
  case yumeami::Direction::UP:
    return TruePos{true_pos.x, true_pos.y - 1};
  case yumeami::Direction::DOWN:
    return TruePos{true_pos.x, true_pos.y + 1};
  case yumeami::Direction::LEFT:
    return TruePos{true_pos.x - 1, true_pos.y};
  case yumeami::Direction::RIGHT:
    return TruePos{true_pos.x + 1, true_pos.y};
  }
  return true_pos;
}


yumeami::DrawPos yumeami::direction_to_draw_pos(const DrawPos &draw_pos,
                                                const Direction &dir) {
  switch (dir) {
  case yumeami::Direction::UP:
    return DrawPos{draw_pos.x, draw_pos.y - 1};
  case yumeami::Direction::DOWN:
    return DrawPos{draw_pos.x, draw_pos.y + 1};
  case yumeami::Direction::LEFT:
    return DrawPos{draw_pos.x - 1, draw_pos.y};
  case yumeami::Direction::RIGHT:
    return DrawPos{draw_pos.x + 1, draw_pos.y};
  }
  return draw_pos;
}
