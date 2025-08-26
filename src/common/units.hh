/**
 * @file units.hh
 * @brief Simple unit wrappers
 */

#pragma once
namespace yumeami {

  /**
   * @class tile
   * @brief Simple wrapper for tile unit.
   *
   */
  struct tile {
    float val;
    tile(float val) : val(val) {}
    tile(int val) : val(static_cast<float>(val)) {}

    operator float() const { return val; }

    // @brief truncate float value into int
    int trunc() const { return static_cast<int>(val); }
  };

  /**
   * @class spx
   * @brief Simple wrapper for sprite pixel unit.
   *
   */
  struct spx {
    float val;
    spx(float val) : val(val) {}
    spx(int val) : val(static_cast<float>(val)) {}

    operator float() const { return val; }

    // @brief truncate float value into int
    int trunc() const { return static_cast<int>(val); }
  };

} // namespace yumeami
