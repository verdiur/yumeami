#include "resources/texture/cache.hh"
#include "common/raii/texture.hh"
#include "spdlog/spdlog.h"
#include <memory>


yumeami::SafeTextureLoader::result_type
yumeami::SafeTextureLoader::operator()(std::string path) {
  SafeTexture res(path);
  if (!res.valid) {
    spdlog::error("[SafeTextureCache] could not load texture");
    return nullptr;
  }
  return std::make_shared<SafeTexture>(std::move(res));
}
