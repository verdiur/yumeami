#pragma once
#include "common/units/tx.hh"
#include "resources/texture/fwd.hh"
#include <entt/resource/resource.hpp>
#include <optional>
#include <raylib.h>
namespace yumeami {

  struct Spritesheet {
    int rows;
    int cols;
    tx sprite_width;
    tx sprite_height;

    entt::resource<SafeTexture> texture;

    /**
     * @brief Spritesheet constructor that also creates a new texture.
     * @param tex_pool texture pool
     * @param path path to the file
     * @param rows amount of sprites per row
     * @param cols amount of sprites per column
     * @param sprite_width width of a single sprite
     * @param sprite_height height of a single sprite
     */
    Spritesheet(SafeTextureCache &tex_cache, std::string path, int rows,
                int cols, tx sprite_width, tx sprite_height);

    /**
     * @brief Get source rectangle of a sprite, for draw_*_ex or draw_*_pro.
     * @param row
     * @param col
     * @return source Rectangle
     */
    std::optional<Rectangle> source_rec_at(int row, int col);
  };

} // namespace yumeami
