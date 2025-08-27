#include "graphics/texture.hh"
#include "common/units.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <optional>


bool yumeami::SheetPool::load_sheet(std::filesystem::path path, spx spr_width,
                                    spx spr_height, std::string key) {
  if (pool.contains(key)) {
    spdlog::error("SheetPool - key already exists");
    return false;
  }

  Texture tex = LoadTexture(path.c_str());
  if (!IsTextureValid(tex)) {
    spdlog::error("SheetPool - invalid texture");
    return false;
  }

  int rows = (int)tex.height / spr_height.trunc();
  int cols = (int)tex.width / spr_width.trunc();
  auto sheet_ptr =
      std::make_shared<Sheet>(Sheet{tex, spr_width, spr_height, rows, cols});

  pool.emplace(key, sheet_ptr);
  spdlog::info("SheetPool - {} loaded with key {}", path.string(), key);
  return true;
}


bool yumeami::SheetPool::unload_sheet(std::string key) {

  if (!pool.contains(key)) {
    spdlog::error("SheetPool - key {} not found", key);
    return false;
  }

  auto sheet_ptr = pool.at(key);
  if (!sheet_ptr.unique()) {
    spdlog::error("SheetPool - sheet with key {} is currently in use", key);
    return false;
  }

  UnloadTexture(sheet_ptr->tex);
  pool.erase(key);
  spdlog::info("SheetPool - unloaded sheet with key {}", key);
  return true;
}


std::optional<std::shared_ptr<yumeami::Sheet>>
yumeami::SheetPool::get_sheet(std::string key) {

  if (!pool.contains(key)) {
    spdlog::debug("SheetPool - could not get sheet with key {}", key);
    return std::nullopt;
  }

  auto ptr = pool.at(key);
  return ptr;
}
