/**
 * @file raii.hh
 * @brief RAII wrappers around C structs
 */

#pragma once
#include "raylib.h"
#include <string>
namespace yumeami {

  /**
   * @class SafeTexture
   * @brief RAII wrapper around raylib's Texture struct
   *
   */
  struct SafeTexture {
    Texture t;
    bool valid;

    // no copy
    SafeTexture(const SafeTexture &) = delete;
    SafeTexture &operator=(const SafeTexture &) = delete;

    SafeTexture(std::string path);
    ~SafeTexture();

    // move
    SafeTexture(SafeTexture &&other) noexcept;
    SafeTexture &operator=(SafeTexture &&other) noexcept;

    // access
    Texture *operator->();
    const Texture *operator->() const;

    // cast
    operator Texture &();
    operator const Texture &() const;
  };
  using SafeTex = SafeTexture;

  /**
   * @class SafeRenderTexture
   * @brief RAII wrapprt around raylib's RenderTexture struct
   *
   */
  struct SafeRenderTexture {
    RenderTexture rt;
    bool valid;

    // no copy
    SafeRenderTexture(const SafeRenderTexture &) = delete;
    SafeRenderTexture &operator=(const SafeRenderTexture &) = delete;

    SafeRenderTexture(int width, int height);
    ~SafeRenderTexture();

    // access
    RenderTexture *operator->();
    const RenderTexture *operator->() const;

    // cast
    operator RenderTexture &();
    operator const RenderTexture &() const;
  };
  using SafeRenderTex = SafeRenderTexture;

} // namespace yumeami
