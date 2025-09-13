/**
 * @file grid.hh
 * @brief Grid class (2d array implemented as a 1d vector)
 */

#pragma once
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

    /**
     * @brief Access to an element of grid
     * @param x
     * @param y
     * @return reference to element
     */
    T &at(int x, int y) { return vec.at((x + 1) * y + x); }

    /**
     * @brief Const access to an element of grid
     * @param x
     * @param y
     * @return const ref to element
     */
    const T &at(int x, int y) const { return vec.at((x + 1) * y + x); }

    int size() const { return vec.size(); }

    // std::vector<T> *operator->() { return vec; }
    // const std::vector<T> *operator->() const { return vec; }
  };

} // namespace yumeami
