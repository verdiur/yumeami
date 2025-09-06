#include "common/raii.hh"
#include "raylib.h"


/* RAIITexture ****************************************************************/


yumeami::RAIITexture::RAIITexture(const std::string path)
    : tex(LoadTexture(path.c_str())), valid(true) {
  if (!IsTextureValid(tex)) {
    valid = false;
  }
}


yumeami::RAIITexture::~RAIITexture() {
  if (tex.id != 0) {
    UnloadTexture(tex);
  }
}


Texture *yumeami::RAIITexture::operator->() { return &tex; }
const Texture *yumeami::RAIITexture::operator->() const { return &tex; }
yumeami::RAIITexture::operator Texture() const { return tex; }
