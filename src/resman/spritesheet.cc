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
  if (tex_height <= 0 || tex_width <= 0) {
    return std::nullopt;
  }

  return Spritesheet{
      .tex = std::move(tex),
      .spr_width = spr_width,
      .spr_height = spr_height,
      .rows = tex_height / (int)spr_height,
      .cols = tex_width / (int)spr_width,
  };
}
