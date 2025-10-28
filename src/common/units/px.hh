#pragma once
namespace yumeami {

  /**
   * @class px
   * @brief Pixel unit. This is the smallest drawable unit in the raylib
   * window.
   *
   */
  struct px {
    float val;

    px(double val) : val(val) {}
    px(float val) : val(val) {}
    px(int val) : val(val) {}

    operator double() const { return val; }
    operator float() const { return val; }
    operator int() const { return val; }

    px &operator+=(const px &rhs) {
      this->val += rhs.val;
      return *this;
    }

    px &operator-=(const px &rhs) {
      this->val -= rhs.val;
      return *this;
    }
  };

} // namespace yumeami
