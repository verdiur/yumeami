/**
 * @file static_string.hh
 * @brief Static string NTTP class
 */

#pragma once
#include <algorithm>
#include <cstddef>
#include <string>
namespace yumeami {

  template <size_t N> struct StaticString {
    char value[N];
    constexpr StaticString(const char (&str)[N]) { std::copy_n(str, N, value); }
    constexpr operator std::string() const { return {value, N - 1}; }
  };

} // namespace yumeami
