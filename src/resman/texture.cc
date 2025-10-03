#include "resman/texture.hh"
#include "common/raii.hh"
#include <optional>


std::optional<yumeami::SafeTexture> yumeami::TextureLoader::operator()() const {
  SafeTexture tex(path);
  if (!tex.valid) {
    spdlog::error("[TextureLoader] invalid texture for path {}", path);
    return std::nullopt;
  }

  int tex_height = tex->height;
  int tex_width = tex->width;
  if (tex_height <= 0 || tex_width <= 0) {
    spdlog::error("[TextureLoader] invalid dimensions for path {}", path);
    return std::nullopt;
  }

  return tex;
}
