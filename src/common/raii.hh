/**
 * @file raii.hh
 * @brief RAII wrappers around C structs
 */

#pragma once
#include "raylib.h"
#include <string>
namespace yumeami {

  struct SafeTexture {
    Texture t;
    bool valid;

    SafeTexture(std::string path);
    ~SafeTexture();
    Texture *operator->();
    const Texture *operator->() const;
    operator Texture &();
    operator const Texture &() const;
  };
  using SafeTex = SafeTexture;

  struct SafeRenderTexture {
    RenderTexture rt;
    bool valid;

    SafeRenderTexture(int width, int height);
    ~SafeRenderTexture();
    RenderTexture *operator->();
    const RenderTexture *operator->() const;
    operator RenderTexture &();
    operator const RenderTexture &() const;
  };
  using SafeRenderTex = SafeRenderTexture;

} // namespace yumeami
