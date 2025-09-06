#include "resman/texture.hh"
#include "common/raii.hh"
#include "spdlog/spdlog.h"
#include <cassert>
#include <string>


/* SpritesheetPool ************************************************************/


bool yumeami::SpritesheetPool::contains(std::string key) const {
  return pool.contains(key);
}


bool yumeami::SpritesheetPool::valid(std::string key) const {
  assert(contains(key));
  return pool.at(key).tex.valid;
}


bool yumeami::SpritesheetPool::load(std::string key, std::string path,
                                    spx spr_width, spx spr_height) {
  if (contains(key)) {
    spdlog::error("[SpritesheetPool] could not load {}: key is already in pool",
                  path);
    return false;
  }
  SafeTexture tex(path);
  if (!tex.valid) {
    spdlog::error("[SpritesheetPool] could not load {}");
    return false;
  }
  Spritesheet sheet{
      .tex = tex,
      .spr_width = spr_width,
      .spr_height = spr_height,
      .rows = tex->height / (int)spr_height,
      .cols = tex->width / (int)spr_width,
  };
  pool.emplace(key, sheet);
  spdlog::info("[SpritesheetPool] loaded {} with key {}", path, key);
  return true;
}


bool yumeami::SpritesheetPool::unload(std::string key) {
  if (!contains(key)) {
    spdlog::error("[SpritesheetPool] could not unload: key not found");
    return false;
  }
  pool.erase(key);
  spdlog::info("[SpritesheetPool] unloaded spritesheet with key {}", key);
  return true;
}


void yumeami::SpritesheetPool::clear() {
  pool.clear();
  spdlog::info("[SpritesheetPool] unloaded all spritesheets");
}


yumeami::Spritesheet *yumeami::SpritesheetPool::get(std::string key) {
  if (!contains(key)) {
    spdlog::error("[SpritesheetPool] could not get spritesheet: key not found");
    return nullptr;
  }
  return &pool.at(key);
}


const yumeami::Spritesheet *
yumeami::SpritesheetPool::get(std::string key) const {
  return get(key);
}
