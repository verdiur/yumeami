#include "resources/spritesheet/cache.hh"
#include "common/units/tx.hh"
#include "model/spritesheet/spritesheet.hh"
#include <memory>
#include <spdlog/spdlog.h>


yumeami::SpritesheetLoader::result_type
yumeami::SpritesheetLoader::operator()(SafeTextureCache &tex_cache,
                                       std::string path, int rows, int cols,
                                       tx sprite_width, tx sprite_height) {
  std::optional<Spritesheet> res = Spritesheet::create(
      tex_cache, path, rows, cols, sprite_width, sprite_height);

  if (!res) {
    spdlog::error("[SpritesheetCache] could not load spritesheet");
    return nullptr;
  }

  return std::make_shared<Spritesheet>(std::move(res.value()));
}
