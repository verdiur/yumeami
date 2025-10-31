#include "resources/render_texture_cache.hh"
#include "common/raii/render_texture.hh"
#include <memory>


yumeami::SafeRenderTextureLoader::result_type
yumeami::SafeRenderTextureLoader::operator()(int width, int height) {
  SafeRenderTexture res(width, height);
  if (!res.valid) {
    return nullptr;
  }
  return std::make_shared<SafeRenderTexture>(std::move(res));
}
