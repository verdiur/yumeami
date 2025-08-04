#include "game/conversions.hh"
#include "game/components.hh"
#include "util/direction.hh"

yumeami::DrawTilePos yumeami::to_draw_tile_pos(TrueTilePos true_pos) {
  return DrawTilePos{static_cast<float>(true_pos.x), static_cast<float>(true_pos.y)};
}

yumeami::TrueTilePos yumeami::to_true_tile_pos(DrawTilePos draw_pos) {
  return TrueTilePos{static_cast<int>(draw_pos.x), static_cast<int>(draw_pos.y)};
}

yumeami::TrueTilePos yumeami::calc_true_tile_pos_from_direction4(TrueTilePos true_pos,
                                                                 Direction4 direction) {
  switch (direction) {
  case Direction4::LEFT:
    return TrueTilePos{true_pos.x - 1, true_pos.y};
  case Direction4::RIGHT:
    return TrueTilePos{true_pos.x + 1, true_pos.y};
  case Direction4::TOP:
    return TrueTilePos{true_pos.x, true_pos.y - 1};
  case Direction4::BOTTOM:
    return TrueTilePos{true_pos.x, true_pos.y + 2};
  case Direction4::NONE:
    return true_pos;
  }
  return true_pos;
}
