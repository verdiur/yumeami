#pragma once
#include "common/units/fwd.hh"
#include "entt/resource/cache.hpp"
#include "model/spritesheet/fwd.hh"
#include "resources/texture/fwd.hh"
#include <memory>
namespace yumeami {

  struct SpritesheetLoader final {
    using result_type = std::shared_ptr<Spritesheet>;
    result_type operator()(SafeTextureCache &tex_cache, std::string name,
                           std::string path, int rows, int cols,
                           tx sprite_width, tx sprite_height);
  };

  using SpritesheetCache = entt::resource_cache<Spritesheet, SpritesheetLoader>;

} // namespace yumeami
