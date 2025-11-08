#pragma once
#include "common/raii/fwd.hh"
#include <entt/resource/fwd.hpp>
namespace yumeami {

  struct SafeRenderTextureLoader;
  using SafeRenderTextureCache =
      entt::resource_cache<SafeRenderTexture, SafeRenderTextureLoader>;
  struct SafeRenderTexturePool;

  struct SafeTextureLoader;
  using SafeTextureCache = entt::resource_cache<SafeTexture, SafeTextureLoader>;
  struct SafeTexturePool;

} // namespace yumeami
