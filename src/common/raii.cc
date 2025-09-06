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
