#include "resources/render_texture/cache.hh"
#include "common/raii/render_texture.hh"
#include <memory>
#include <spdlog/spdlog.h>


yumeami::SafeRenderTextureLoader::result_type
yumeami::SafeRenderTextureLoader::operator()(int width, int height) {
  SafeRenderTexture res(width, height);
  if (!res.valid) {
    spdlog::error("[SafeRenderTextureCache] could not load render texture");
    return nullptr;
  }
  return std::make_shared<SafeRenderTexture>(std::move(res));
}
