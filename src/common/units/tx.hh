#pragma once
namespace yumeami {

  /**
   * @class tx
   * @brief Texel (TEXture ELement) unit. This also corresponds to the smallest
   * unit used in the viewport, as the viewport itself is measured in texels.
   *
   */
  struct tx {
    float val;

    tx(double val) : val(val) {}
    tx(float val) : val(val) {}
    tx(int val) : val(val) {}

    operator double() const { return val; }
    operator float() const { return val; }
    operator int() const { return val; }

    tx &operator+=(const tx &rhs) {
      this->val += rhs.val;
      return *this;
    }

    tx &operator-=(const tx &rhs) {
      this->val -= rhs.val;
      return *this;
    }
  };

} // namespace yumeami
