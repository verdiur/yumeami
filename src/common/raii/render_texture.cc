#include "common/raii/render_texture.hh"
#include "raylib.h"


yumeami::SafeRenderTexture::SafeRenderTexture(int width, int height)
    : rt(LoadRenderTexture(width, height)), valid(true) {
  if (!IsRenderTextureValid(rt)) {
    valid = false;
  }
}


yumeami::SafeRenderTexture::SafeRenderTexture(SafeRenderTexture &&other)
    : rt(other.rt), valid(other.valid) {
  other.valid = false;
  other.rt.id = 0;
  other.rt.texture = {};
  other.rt.depth = {};
}


yumeami::SafeRenderTexture &
yumeami::SafeRenderTexture::operator=(SafeRenderTexture &&other) {
  if (this == &other) {
    return *this;
  }
  if (IsRenderTextureValid(this->rt)) {
    UnloadRenderTexture(this->rt);
  }

  other.rt.id = 0;
  other.rt.texture = {};
  other.rt.depth = {};

  return *this;
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
