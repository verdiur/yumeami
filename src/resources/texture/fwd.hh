#pragma once
#include "common/raii/fwd.hh"
#include <entt/resource/fwd.hpp>
namespace yumeami {

  struct SafeTextureLoader;
  using SafeTextureCache = entt::resource_cache<SafeTexture, SafeTextureLoader>;

} // namespace yumeami
