/**
 * @file texture.hh
 * @brief Simple texture resource management
 */

#pragma once
#include "common/raii.hh"
#include "resman/base.hh"
#include <optional>
#include <string>
namespace yumeami {

  struct TextureLoader {
    std::string path;
    std::optional<SafeTexture> operator()() const;
  };

  using TextureCache =
      ResourceCache<"TextureCache", SafeTexture, TextureLoader>;

} // namespace yumeami
