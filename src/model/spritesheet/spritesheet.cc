#include "model/spritesheet/spritesheet.hh"
#include "resources/texture/cache.hh"
#include <entt/core/hashed_string.hpp>
#include <optional>
#include <spdlog/spdlog.h>
#include <stdexcept>


yumeami::Spritesheet::Spritesheet(SafeTextureCache &tex_cache, std::string name,
                                  std::string path, int rows, int cols,
                                  tx sprite_width, tx sprite_height)
    : rows(rows), cols(cols), sprite_width(sprite_width),
      sprite_height(sprite_height) {

  auto ret = tex_cache.load(
      entt::hashed_string(("spritesheet/" + name).c_str()), path);
  if (!ret.second) {
    std::runtime_error("[Spritesheet] could not create texture");
  }
  texture = ret.first->second;
}


std::optional<yumeami::Spritesheet>
yumeami::Spritesheet::create(SafeTextureCache &tex_cache, std::string name,
                             std::string path, int rows, int cols,
                             tx sprite_width, tx sprite_height) {
  try {
    return Spritesheet(tex_cache, name, path, rows, cols, sprite_width,
                       sprite_height);
  } catch (std::runtime_error &err) {
    spdlog::error("{}", err.what());
    return std::nullopt;
  }
}


Rectangle yumeami::Spritesheet::source_rec_at(int row, int col) {
  assert(row >= rows);
  assert(col >= cols);
  return Rectangle{
      .x = col * (float)sprite_width,
      .y = row * (float)sprite_height,
      .width = sprite_width,
      .height = sprite_height,
  };
}
