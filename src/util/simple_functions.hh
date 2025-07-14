#pragma once

#include "game/simple_components.hh"
#include "util/simple_types.hh"

namespace yumeami {

  /**
   * @brief Calculate position targeted by Facing component
   *
   * @param facing facing component
   * @param position position component
   * @return targeted position
   */
  FloatTilePosition calculate_float_position_from_facing(
    const comp::Facing& facing,
    const FloatTilePosition& position);

  /**
   * @brief Calculate position targeted by Facing component
   *
   * @param facing facing component
   * @param position position component
   * @return targeted position
   */
  IntTilePosition calculate_int_position_from_facing(const comp::Facing& facing,
                                                     const IntTilePosition& position);

} // namespace yumeami
