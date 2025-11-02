#pragma once
namespace yumeami {

  /**
   * @class tile
   * @brief Tile unit. This corresponds to the size of a world tile. It is
   * defined per-world as a fixed amount of texels.
   *
   */
  struct tile {
    float val;

    tile(double val) : val(val) {}
    tile(float val) : val(val) {}
    tile(int val) : val(val) {}
    tile() : val() {}

    operator double() const { return val; }
    operator float() const { return val; }
    operator int() const { return val; }

    tile &operator+=(const tile &rhs) {
      this->val += rhs.val;
      return *this;
    }

    tile &operator-=(const tile &rhs) {
      this->val -= rhs.val;
      return *this;
    }
  };

} // namespace yumeami
