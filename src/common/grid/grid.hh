#pragma once
#include <format>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
namespace yumeami {

  /**
   * @brief Grid class that represents a 2d array. Internally it's a row vector.
   * Current implementation does not include resizing.
   *
   * @tparam T any type
   * @param width
   * @param height
   * @param init_val initialization value. All elements of the vector will be
   * set to this value.
   * @return
   */
  template <class T> class Grid {
    int width;
    int height;
    std::vector<T> vec;

  public:
    Grid(int width, int height, T init_val)
        : width(width), height(height), vec(width * height, init_val) {}

    Grid() : width(1), height(1), vec(1, 0) {}

    /**
     * @brief Access to an element of grid
     * @param x
     * @param y
     * @return reference to element
     */
    T &at(int x, int y) {
      try {
        return vec.at(width * y + x);
      } catch (std::out_of_range &e) {
        throw std::out_of_range(std::format(
            "[Grid] index {}, {} ({}) out of range", x, y, width * y + x));
      }
    }

    /**
     * @brief Const access to an element of grid
     * @param x
     * @param y
     * @return const ref to element
     */
    const T &at(int x, int y) const {
      try {
        return vec.at(width * y + x);
      } catch (std::out_of_range &e) {
        throw std::out_of_range(std::format(
            "[Grid] index {}, {} ({}) out of range", x, y, width * y + x));
      }
    }

    int area() const { return vec.size(); }
    int get_width() const { return width; }
    int get_height() const { return height; }

    std::string str() {
      std::stringstream stream{};
      for (int y = 0; y < get_height(); y++) {
        for (int x = 0; x < get_width(); x++) {
          stream << at(x, y) << ", ";
        }
        stream << "\n";
      }
      return stream.str();
    }

    // std::vector<T> *operator->() { return vec; }
    // const std::vector<T> *operator->() const { return vec; }
  };

} // namespace yumeami
