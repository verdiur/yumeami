/**
 * @file texture.hh
 * @brief Texture structs and management
 */

#pragma once
#include "common/raii.hh"
#include "common/units.hh"
#include <string>
#include <unordered_map>
namespace yumeami {

  struct Spritesheet {
    SafeTexture tex;
    spx spr_width;
    spx spr_height;
    int rows;
    int cols;
  };

  /**
   * @class SpritesheetPool
   * @brief Pool of spritesheets. Contains plain spritesheet instances, not
   * pointers.
   *
   */
  struct SpritesheetPool {
  private:
    std::unordered_map<std::string, Spritesheet> pool = {};

  public:
    bool contains(std::string key) const;
    bool valid(std::string key) const;
    bool load(std::string key, std::string path, spx spr_width, spx spr_height);
    bool unload(std::string key);
    void clear();
    Spritesheet *get(std::string key);
    const Spritesheet *get(std::string key) const;
  };

  using Sheet = Spritesheet;
  using SheetPool = SpritesheetPool;

} // namespace yumeami
