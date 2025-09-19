/**
 * @file spritesheet.hh
 * @brief Spritesheet resource management
 */

#pragma once
#include "common/raii.hh"
#include "common/units.hh"
#include "resman/base.hh"
#include <optional>
namespace yumeami {

  struct Spritesheet {
    SafeTexture tex;
    spx spr_width;
    spx spr_height;
    int rows;
    int cols;
  };

  /**
   * @class SpritesheetLoader
   * @brief Loader for Spritesheet resources
   *
   */
  struct SpritesheetLoader {
    std::string path;
    spx spr_width;
    spx spr_height;
    std::optional<Spritesheet> operator()() const;
  };

  using SpritesheetCache =
      ResourceCache<"SpritesheetCache", Spritesheet, SpritesheetLoader>;

  using SheetCache = SpritesheetCache;
  using Sheet = Spritesheet;
  using SheetLoader = SpritesheetLoader;

} // namespace yumeami
