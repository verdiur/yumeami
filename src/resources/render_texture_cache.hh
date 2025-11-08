#pragma once
#include "common/raii/fwd.hh"
#include "resources/id_counter.hh"
#include <entt/resource/cache.hpp>
#include <memory>
namespace yumeami {

  /**
   * @class SafeRenderTextureLoader
   * @brief Loader for SafeRenderTexture resources.
   *
   */
  struct SafeRenderTextureLoader final {
    using result_type = std::shared_ptr<SafeRenderTexture>;
    result_type operator()(int width, int height);
  };

  using SafeRenderTextureCache =
      entt::resource_cache<SafeRenderTexture, SafeRenderTextureLoader>;

  /**
   * @class SafeRenderTexturePool
   * @brief Combination of cache and counter
   *
   */
  struct SafeRenderTexturePool {
    SafeRenderTextureCache cache;
    IdCounter counter;
  };

} // namespace yumeami
