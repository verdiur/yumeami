#include "model/spritesheet/spritesheet.hh"
#include "resources/core/id.hh"
#include "resources/texture/cache.hh"
#include <entt/core/hashed_string.hpp>
#include <optional>


yumeami::Spritesheet::Spritesheet(SafeTextureCache &tex_cache, std::string path,
                                  int rows, int cols, tx sprite_width,
                                  tx sprite_height)
    : rows(rows), cols(cols), sprite_width(sprite_width),
      sprite_height(sprite_height) {

  auto ret = tex_cache.load(generate_id(), path);
  if (!ret.second) {
    std::runtime_error("[Spritesheet] could not create texture");
  }
  texture = ret.first->second;
}


std::optional<Rectangle> yumeami::Spritesheet::source_rec_at(int row, int col) {
  if (row >= rows) return std::nullopt;
  if (col >= cols) return std::nullopt;
  return Rectangle{
      .x = col * (float)sprite_width,
      .y = row * (float)sprite_height,
      .width = sprite_width,
      .height = sprite_height,
  };
}
