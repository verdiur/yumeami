/**
 * @file raii.cpp
 * @brief RAII wrappers around C structs
 */

#pragma once
#include "raylib.h"
#include <string>
namespace yumeami {

  /**
   * @class RAIITex
   * @brief RAII Wrapper around raylib's Texture
   *
   */
  struct RAIITexture {
    Texture tex;
    bool valid;
    RAIITexture(const std::string path);
    ~RAIITexture();

    Texture *operator->();
    const Texture *operator->() const;
    operator Texture() const;
  };
  typedef RAIITexture RAIITex;

} // namespace yumeami
