/**
 * @file texture.hh
 * @brief Texture structs and management
 */

#pragma once
#include "common/units.hh"
#include "raylib.h"
#include <filesystem>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
namespace yumeami {

  struct Sheet {
    Texture tex;
    spx spr_width;
    spx spr_height;
    int rows; // aka height
    int cols; // aka width
  };

  struct SheetPool {
    std::unordered_map<std::string, std::shared_ptr<Sheet>> pool = {};
    bool contains(std::string key);
    /**
     * @brief Create new spritesheet and add it to the pool. Row and column
     * count are calculated automatically.
     *
     * @param path path to texture file
     * @param spr_width sprite width
     * @param spr_height sprite height
     * @return exit code
     */
    bool load_sheet(std::filesystem::path path, spx spr_width, spx spr_height,
                    std::string key);
    /**
     * @brief Unload spritesheet and remove it from the pool.
     * @param key
     * @return exit code
     */
    bool unload_sheet(std::string key);
    /**
     * @brief Clear the entire pool. Be wary that it does NOT check for pointer
     * usage.
     */
    void clear();
    /**
     * @brief Create shared_ptr to sheet in the pool.
     * @param key
     * @return shared_ptr to sheet, nullptr if sheet not found
     */
    std::optional<std::shared_ptr<Sheet>> get_sheet(std::string key) const;
  };

  /**
   * @brief Unload spritesheets from a spritesheet pool.
   * @param pool
   * @param keys
   * @param force If true, will unload all specified sheets, skipping invalid
   * keys. If false, will only unload if all keys are valid.
   * @return
   */
  bool unload_sheets_from_pool(SheetPool &pool,
                               const std::vector<std::string> &keys,
                               bool force);

} // namespace yumeami
