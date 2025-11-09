#pragma once
#include "common/defines.hh"
#include "model/spritesheet/fwd.hh"
#include "resources/spritesheet/cache.hh"
#include <entt/resource/resource.hpp>
namespace yumeami {

  struct Sprite YUMEAMI_COMPONENT {
    entt::resource<Spritesheet> spritesheet;
    int row;
    int col;

    Sprite(SpritesheetCache &sheet_cache, std::string sheet_name, int row,
           int col);
  };

} // namespace yumeami
