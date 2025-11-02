#pragma once
#include <raylib.h>
#include <string>
namespace yumeami {

  /**
   * @class SafeTexture
   * @brief RAII wrapper around raylib's Texture. Code adapted from raylib-cpp.
   * A SafeTexture cannot be copied.
   *
   */
  struct SafeTexture {
  private:
    Texture t;

  public:
    bool valid;

    SafeTexture(std::string path);
    ~SafeTexture();

    // no copy
    SafeTexture(const SafeTexture &) = delete;
    SafeTexture &operator=(const SafeTexture &) = delete;

    // move
    SafeTexture(SafeTexture &&other);
    SafeTexture &operator=(SafeTexture &&other);

    // access
    Texture *operator->();
    const Texture *operator->() const;

    // cast
    operator Texture &();
    operator const Texture &() const;
  };

} // namespace yumeami
