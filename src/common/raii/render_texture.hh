#pragma once
#include "raylib.h"
namespace yumeami {

  struct SafeRenderTexture {
    RenderTexture rt;
    bool valid;

    SafeRenderTexture(int width, int height);
    ~SafeRenderTexture();

    // no copy
    SafeRenderTexture(const SafeRenderTexture &) = delete;
    SafeRenderTexture &operator=(const SafeRenderTexture &) = delete;

    // access
    RenderTexture *operator->();
    const RenderTexture *operator->() const;

    // cast
    operator RenderTexture &();
    operator const RenderTexture &() const;
  };

} // namespace yumeami
