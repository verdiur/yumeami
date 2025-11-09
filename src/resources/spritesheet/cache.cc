#include "resources/spritesheet/cache.hh"
#include "common/units/tx.hh"
#include "model/spritesheet/spritesheet.hh"
#include <memory>
#include <spdlog/spdlog.h>
#include <stdexcept>


yumeami::SpritesheetLoader::result_type
yumeami::SpritesheetLoader::operator()(SafeTextureCache &tex_cache,
                                       std::string path, int rows, int cols,
                                       tx sprite_width, tx sprite_height) {
  try {
    Spritesheet res(tex_cache, path, rows, cols, sprite_width, sprite_height);
    return std::make_shared<Spritesheet>(std::move(res));

  } catch (std::runtime_error &err) {
    spdlog::error(
        "[SpritesheetCache] could not load spritesheet (caused by {})",
        err.what());
    return nullptr;
  }
}
