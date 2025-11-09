#include "model/components/sprite.hh"
#include <entt/core/hashed_string.hpp>
#include <stdexcept>


yumeami::Sprite::Sprite(SpritesheetCache &sheet_cache, std::string sheet_name,
                        int row, int col)
    : row(row), col(col) {
  spritesheet = sheet_cache[entt::hashed_string(sheet_name.c_str())];
  if (!spritesheet) {
    throw std::runtime_error("[Sprite] could not get spritesheet");
  }
}
