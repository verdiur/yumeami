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
    spdlog::error(
        "[SpritesheetPool] could not load \"{}\": key is already in pool",
        path);
    return false;
  }
  SafeTexture tex(path);
  if (!tex.valid) {
    spdlog::error("[SpritesheetPool] could not load \"{}\"");
    return false;
  }

  // must fetch texture width and height beforehand because std::move()
  // zeroes out all fields
  int tex_height = tex->height;
  int tex_width = tex->width;
  Spritesheet sheet{
      .tex = std::move(tex),
      .spr_width = spr_width,
      .spr_height = spr_height,
      .rows = tex_height / (int)spr_height,
      .cols = tex_width / (int)spr_width,
  };

  int sheet_id = sheet.tex->id;
  pool.try_emplace(key, std::move(sheet));
  spdlog::info("[SpritesheetPool] loaded \"{}\" ({}) with key \"{}\"", path,
               sheet_id, key);
  return true;
}


bool yumeami::SpritesheetPool::unload(std::string key) {
  if (!contains(key)) {
    spdlog::error("[SpritesheetPool] could not unload: key not found");
    return false;
  }
  pool.erase(key);
  spdlog::info("[SpritesheetPool] unloaded spritesheet with key \"{}\"", key);
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
