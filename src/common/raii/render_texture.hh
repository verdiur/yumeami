#pragma once
#include <raylib.h>
namespace yumeami {

  /**
   * @class SafeRenderTexture
   * @brief RAII wrapper around raylib's RenderTexture. Code adapted from
   * raylib-cpp. A SafeRenderTexture cannot be copied.
   *
   */
  struct SafeRenderTexture {
    RenderTexture rt;
    bool valid;

    SafeRenderTexture(int width, int height);
    ~SafeRenderTexture();

    // no copy
    SafeRenderTexture(const SafeRenderTexture &) = delete;
    SafeRenderTexture &operator=(const SafeRenderTexture &) = delete;

    // move
    SafeRenderTexture(SafeRenderTexture &&other);
    SafeRenderTexture &operator=(SafeRenderTexture &&other);

    // access
    RenderTexture *operator->();
    const RenderTexture *operator->() const;

    // cast
    operator RenderTexture &();
    operator const RenderTexture &() const;
  };

} // namespace yumeami
