#include "resources/texture_cache.hh"
#include "common/raii/texture.hh"
#include <memory>


yumeami::SafeTextureLoader::result_type
yumeami::SafeTextureLoader::operator()(std::string path) {
  SafeTexture res(path);
  if (!res.valid) return nullptr;

  return std::make_shared<SafeTexture>(std::move(res));
}
