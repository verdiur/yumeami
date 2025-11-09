#pragma once
#include "resources/render_texture/cache.hh"
#include "resources/texture/cache.hh"
namespace yumeami {

  /**
   * @class ResourceCaches
   * @brief All resource caches needed in the game, wrapped into a convenient
   * POD struct. This helps us keep code organized and also helps us reduce the
   * amount of includes in main.cc.
   *
   */
  struct ResourceCaches {
    SafeTextureCache texture_pool;
    SafeRenderTextureCache render_texture_pool;
  };

} // namespace yumeami
