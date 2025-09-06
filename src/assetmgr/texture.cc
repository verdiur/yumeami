#include "assetmgr/texture.hh"
#include "common/raii.hh"
#include "common/units.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>


/* SheetPool ******************************************************************/


bool yumeami::SheetPool::contains(std::string key) const {
  return pool.contains(key);
}


bool yumeami::SheetPool::load_sheet(std::filesystem::path path, spx spr_width,
                                    spx spr_height, std::string key) {
  if (contains(key)) {
    spdlog::error("SheetPool - key already exists");
    return false;
  }
  RAIITex tex(path);
  if (!tex.valid) {
    spdlog::error("SheetPool - invalid texture");
    return false;
  }
  int rows = (int)tex->height / spr_height.trunc();
  int cols = (int)tex->width / spr_height.trunc();
  pool.emplace(key, Sheet{tex, spr_width, spr_height, rows, cols});
  spdlog::info("SheetPool - {} loaded with key {}", path.string(), key);
  return true;
}


bool yumeami::SheetPool::unload_sheet(std::string key) {
  if (contains(key)) {
    spdlog::error("SheetPool - key {} not found", key);
    return false;
  }
  pool.erase(key);
  spdlog::info("SheetPool - unloaded sheet with key {}", key);
  return true;
}


void yumeami::SheetPool::clear() { pool.clear(); }


yumeami::Sheet *yumeami::SheetPool::get_sheet(std::string key) {
  if (!contains(key)) {
    spdlog::error("SheetPool - key {} not found", key);
    return nullptr;
  }
  return &pool.at(key);
}


/* Free functions *************************************************************/


bool yumeami::unload_sheets_from_pool(SheetPool &pool,
                                      const std::vector<std::string> &keys) {
  for (std::string k : keys) {
    if (!pool.contains(k)) {
      spdlog::warn("SheetPool - could not get sheet with key {}. No "
                   "spritesheets will be unloaded.",
                   k);
      return false;
    }
  }
  for (std::string k : keys) {
    pool.unload_sheet(k);
  }
  return true;
}
