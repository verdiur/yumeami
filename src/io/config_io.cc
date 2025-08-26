#include "io/config_io.hh"
#include "raylib.h"
#include "rfl/json/read.hpp"
#include "rfl/json/write.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <optional>
#include <string>


std::optional<yumeami::ConfigSpec> yumeami::parse_config(std::filesystem::path cfg_path) {

  // check filename
  if (!cfg_path.has_filename()) {
    spdlog::error("path must point to a file");
    return std::nullopt;
  }

  // load file
  char *cfg_buf = LoadFileText(cfg_path.c_str());
  if (!cfg_buf) {
    spdlog::error("could not load world config");
    return std::nullopt;
  }

  // parse file
  auto parse_result = rfl::json::read<ConfigSpec>(cfg_buf);
  if (!parse_result) {
    spdlog::error("could not load configuration");
    UnloadFileText(cfg_buf);
    return std::nullopt;
  }

  UnloadFileText(cfg_buf);
  return parse_result.value();
}


void yumeami::write_config(const ConfigSpec &spec, std::filesystem::path file_path) {
  std::string write_result = rfl::json::write(spec);
  if (!SaveFileText(file_path.c_str(), write_result.data())) {
    spdlog::warn("could not write configuration");
    return;
  }
  spdlog::info("configuration written to {}", file_path.string());
}


void yumeami::load_config(const ConfigSpec &spec) {
  SetWindowSize(spec.window_width.get(), spec.window_height.get());
  if (spec.vsync.get()) {
    SetWindowState(FLAG_VSYNC_HINT);
  }
  spdlog::info("configuration loaded");
}
