#pragma once

#include "game/component/simple_components.hh"
#include "util/simple_types.hh"

namespace yumeami {

/**
 * @brief Calculate position targeted by Facing component
 *
 * @param facing facing component
 * @param position position component
 * @return targeted position
 */
FloatTilePosition
calculate_facing_float_position(const c::Facing& facing,
                                const c::TrueTilePosition& position);

/**
 * @brief Calculate position targeted by Facing component
 *
 * @param facing facing component
 * @param position position component
 * @return targeted position
 */
IntTilePosition
calculate_facing_int_position(const c::Facing& facing,
                              const c::TrueTilePosition& position);

} // namespace yumeami
