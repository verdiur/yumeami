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

    static std::optional<Spritesheet> create(SafeTextureCache &tex_cache,
                                             std::string name, std::string path,
                                             int rows, int cols,
                                             tx sprite_width, tx sprite_height);

    /**
     * @brief Get source rectangle of a sprite, for draw_*_ex or draw_*_pro.
     * @param row
     * @param col
     * @return source Rectangle
     */
    Rectangle source_rec_at(int row, int col);

  private:
    /**
     * @brief Spritesheet constructor that also creates a new texture.
     * @param tex_cache texture cache
     * @param name name that will be used as the ID in the cache.
     * @param path path to the file
     * @param rows amount of sprites per row
     * @param cols amount of sprites per column
     * @param sprite_width width of a single sprite
     * @param sprite_height height of a single sprite
     * @throws runtime_error if texture cannot be created
     */
    Spritesheet(SafeTextureCache &tex_cache, std::string name, std::string path,
                int rows, int cols, tx sprite_width, tx sprite_height);
  };

} // namespace yumeami
