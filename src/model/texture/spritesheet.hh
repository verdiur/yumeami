#pragma once
#include "common/raii/fwd.hh"
#include "common/units/tx.hh"
#include "entt/core/fwd.hpp"
#include "raylib.h"
#include "resources/fwd.hh"
#include <entt/resource/resource.hpp>
#include <optional>
namespace yumeami {

  struct Spritesheet {
    int rows;
    int cols;
    tx sprite_width;
    tx sprite_height;

  private:
    entt::resource<SafeTexture> texture_handle;

  public:
    /**
     * @brief Spritesheet constructor
     * @param tex_cache texture cache
     * @param tex_id identifier of the texture in cache
     * @param rows amount of sprites per row
     * @param cols amount of sprites per column
     * @param sprite_width width of a single sprite
     * @param sprite_height height of a single sprite
     */
    Spritesheet(SafeTexturePool &tex_pool, entt::id_type tex_id, int rows,
                int cols, tx sprite_width, tx sprite_height);

    // /**
    //  * @brief Spritesheet constructor that also creates a new texture.
    //  * @param tex_cache texture cache
    //  * @param path path to the file
    //  * @param rows amount of sprites per row
    //  * @param cols amount of sprites per column
    //  * @param sprite_width width of a single sprite
    //  * @param sprite_height height of a single sprite
    //  */
    // Spritesheet(SafeTextureCache &tex_cache, std::string path, int rows,
    //             int cols, tx sprite_width, tx sprite_height);

    /**
     * @brief Get raw reference to SafeTexture.
     * @return SafeTexture
     */
    SafeTexture &texture();
    const SafeTexture &texture() const;

    /**
     * @brief Get source rectangle of a sprite, for draw_*_ex or draw_*_pro.
     * @param row
     * @param col
     * @return source Rectangle
     */
    std::optional<Rectangle> source_rec_at(int row, int col);
  };

} // namespace yumeami
