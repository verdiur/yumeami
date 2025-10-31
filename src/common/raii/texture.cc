#include "common/raii/texture.hh"
#include "raylib.h"

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

yumeami::SafeTexture::SafeTexture(SafeTexture &&other)
    : t(other.t), valid(other.valid) {
  other.valid = false;
  other.t = {};
}

yumeami::SafeTexture &yumeami::SafeTexture::operator=(SafeTexture &&other) {
  if (this == &other) {
    return *this;
  }
  if (IsTextureValid(t)) {
    UnloadTexture(t);
  }

  t = other.t;
  valid = other.valid;

  other.t = {};

  return *this;
}

Texture *yumeami::SafeTexture::operator->() { return &t; }
const Texture *yumeami::SafeTexture::operator->() const { return &t; }

yumeami::SafeTexture::operator Texture &() { return t; }
yumeami::SafeTexture::operator const Texture &() const { return t; }
