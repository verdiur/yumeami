#include "model/texture/spritesheet.hh"
#include "resources/texture_cache.hh"
#include <entt/core/hashed_string.hpp>
#include <optional>
#include <stdexcept>


yumeami::Spritesheet::Spritesheet(SafeTexturePool &tex_pool,
                                  entt::id_type tex_id, int rows, int cols,
                                  tx sprite_width, tx sprite_height)
    : rows(rows), cols(cols), sprite_width(sprite_width),
      sprite_height(sprite_height), texture_handle(tex_pool.cache[tex_id]) {
  if (!texture_handle) {
    throw std::runtime_error("[Spritesheet] could not get texture from cache");
  }
}


yumeami::SafeTexture &yumeami::Spritesheet::texture() {
  return *texture_handle.handle();
}

const yumeami::SafeTexture &yumeami::Spritesheet::texture() const {
  return *texture_handle.handle();
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
