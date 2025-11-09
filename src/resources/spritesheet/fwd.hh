#pragma once
#include "model/spritesheet/fwd.hh"
#include <entt/resource/fwd.hpp>
namespace yumeami {

  struct SpritesheetLoader;
  using SpritesheetCache = entt::resource_cache<Spritesheet, SpritesheetLoader>;

} // namespace yumeami
