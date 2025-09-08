#include "common/raii.hh"
#include "raylib.h"


/* SafeTexture ****************************************************************/


yumeami::SafeTexture::SafeTexture(std::string path)
    : t(LoadTexture(path.c_str())), valid(true) {
  if (!IsTextureValid(t)) {
    valid = false;
  }
}


yumeami::SafeTexture::~SafeTexture() {
  if (IsTextureValid(t)) {
    UnloadTexture(t);
  }
}


yumeami::SafeTexture::SafeTexture(SafeTexture &&other) noexcept
    : t(other.t), valid(other.valid) {
  other.valid = false;
  other.t.id = 0;
  other.t.width = 0;
  other.t.height = 0;
  other.t.mipmaps = 0;
  other.t.format = 0;
}


yumeami::SafeTexture &
yumeami::SafeTexture::operator=(SafeTexture &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  if (IsTextureValid(t)) {
    UnloadTexture(t);
  }

  t = other.t;
  valid = other.valid;

  other.valid = false;
  other.t.id = 0;
  other.t.width = 0;
  other.t.height = 0;
  other.t.mipmaps = 0;
  other.t.format = 0;

  return *this;
}


Texture *yumeami::SafeTexture::operator->() { return &t; }
const Texture *yumeami::SafeTexture::operator->() const { return &t; }


yumeami::SafeTexture::operator Texture &() { return t; }
yumeami::SafeTexture::operator const Texture &() const { return t; }


/* SafeRenderTexture **********************************************************/


yumeami::SafeRenderTexture::SafeRenderTexture(int width, int height)
    : rt(LoadRenderTexture(width, height)), valid(true) {
  if (!IsRenderTextureValid(rt)) {
    valid = false;
  }
}


yumeami::SafeRenderTexture::~SafeRenderTexture() {
  if (IsRenderTextureValid(rt)) {
    UnloadRenderTexture(rt);
  }
}


RenderTexture *yumeami::SafeRenderTexture::operator->() { return &rt; }
const RenderTexture *yumeami::SafeRenderTexture::operator->() const {
  return &rt;
}


yumeami::SafeRenderTexture::operator RenderTexture &() { return rt; }
yumeami::SafeRenderTexture::operator const RenderTexture &() const {
  return rt;
}
