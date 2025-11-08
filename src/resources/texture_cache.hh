#pragma once
#include "common/raii/fwd.hh"
#include "resources/id_counter.hh"
#include <entt/resource/cache.hpp>
#include <memory>
namespace yumeami {

  /**
   * @class SafeTextureLoader
   * @brief Loader for SafeTexture resources.
   *
   */
  struct SafeTextureLoader final {
    using result_type = std::shared_ptr<SafeTexture>;
    result_type operator()(const std::string path);
  };

  using SafeTextureCache = entt::resource_cache<SafeTexture, SafeTextureLoader>;

  /**
   * @class SafeTexturePool
   * @brief Combination of cache and counter
   *
   */
  struct SafeTexturePool {
    SafeTextureCache cache;
    IdCounter counter;
  };

} // namespace yumeami
