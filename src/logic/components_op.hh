/**
 * @file components_op.hh
 * @brief Common operations on components
 */

#pragma once
#include "common/direction.hh"
#include "logic/components.hh"
namespace yumeami {

  TruePos to_true_pos(const DrawPos &draw_pos);
  DrawPos to_draw_pos(const TruePos &true_pos);

  TruePos direction_to_true_pos(const TruePos &true_pos, const Direction &dir);
  DrawPos direction_to_draw_pos(const DrawPos &draw_pos, const Direction &dir);

} // namespace yumeami
