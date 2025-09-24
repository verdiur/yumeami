/**
 * @file units.hh
 * @brief Simple unit wrappers
 */

#pragma once
#include <functional>
#include <string>
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

    tile &operator+=(const tile &rhs) {
      this->val += rhs.val;
      return *this;
    }

    tile &operator-=(const tile &rhs) {
      this->val -= rhs.val;
      return *this;
    }

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

    spx &operator+=(const spx &rhs) {
      this->val += rhs.val;
      return *this;
    }

    spx &operator-=(const spx &rhs) {
      this->val -= rhs.val;
      return *this;
    }

    // @brief truncate float value into int
    int trunc() const { return static_cast<int>(val); }
  };

  /**
   * @class spritesheet_id
   * @brief Simple wrapper for a spritesheet id. You can construct an id with a
   * string. The constructed value will be a hash of that string.
   *
   */
  struct spritesheet_id {
    size_t id;
    spritesheet_id(size_t id) : id(id) {}
    spritesheet_id(std::string str) : id(std::hash<std::string>{}(str)) {}
    operator size_t() const { return id; }
  };

  /**
   * @class texture_id
   * @brief Simple wrapper for a texture id. You can construct an id with a
   * string. The constructed value will be a hash of that string.
   *
   */
  struct texture_id {
    size_t id;
    texture_id(size_t id) : id(id) {}
    texture_id(std::string str) : id(std::hash<std::string>{}(str)) {}
    operator size_t() const { return id; }
  };

  using sheet_id = spritesheet_id;

} // namespace yumeami
