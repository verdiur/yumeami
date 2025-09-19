#include "resman/spritesheet.hh"
#include "spdlog/spdlog.h"
#include <optional>


std::optional<yumeami::Spritesheet>
yumeami::SpritesheetLoader::operator()() const {
  SafeTexture tex(path);
  if (!tex.valid) {
    spdlog::error("[SpritesheetLoader] invalid texture for path {}", path);
    return std::nullopt;
  }

  int tex_height = tex->height;
  int tex_width = tex->width;
  return Spritesheet{
      .tex = std::move(tex),
      .spr_width = spr_width,
      .spr_height = spr_height,
      .rows = tex_height / (int)spr_height,
      .cols = tex_width / (int)spr_width,
  };
}
