/**
 * @file texture.hh
 * @brief Texture structs and management
 */

#pragma once
#include "common/raii.hh"
#include "common/units.hh"
#include <filesystem>
#include <unordered_map>
#include <vector>
namespace yumeami {

  struct Sheet {
    RAIITex tex;
    spx spr_width;
    spx spr_height;
    int rows; // aka height
    int cols; // aka width
  };

  struct SheetPool {
    std::unordered_map<std::string, Sheet> pool = {};
    bool contains(std::string key) const;
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
     * @brief Unload spritesheet and remove it from the pool. Does NOT check for
     * pointer usage.
     *
     * @param key
     * @return exit code
     */
    bool unload_sheet(std::string key);
    /**
     * @brief Clear the entire pool. Be aware that it does NOT check
     * for pointer usage.
     */
    void clear();
    /**
     * @brief Get pointer to spritesheet
     * @param key
     * @return shared_ptr to sheet, nullptr if sheet not found
     */
    Sheet *get_sheet(std::string key);
  };

  /**
   * @brief Unload and delete multiple spritesheets from a spritesheet pool.
   * Will only unload anything if all keys are valid. Does NOT check for pointer
   * usage.
   *
   * @param pool
   * @param keys
   * @return true if successful, false if some keys are invalid
   */
  bool unload_sheets_from_pool(SheetPool &pool,
                               const std::vector<std::string> &keys);

  /**
   * @brief Unload and delete multiple spritesheets from a spritesheet pool.
   * Will skip over invalid keys. Does NOT check for pointer usage.
   *
   * @param pool
   * @param keys
   * @return true if successful, false if some keys are invalid
   */
  bool unload_sheets_from_pool_force(SheetPool &pool,
                                     const std::vector<std::string> &keys);

} // namespace yumeami
