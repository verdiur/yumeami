#include "io/config_io.hh"
#include "raylib.h"
#include "rfl/json/read.hpp"
#include "rfl/json/write.hpp"
#include "spdlog/spdlog.h"
#include <optional>
#include <string>


std::optional<yumeami::ConfigSpec> yumeami::load_config(std::string buffer) {
  auto read_result = rfl::json::read<ConfigSpec>(buffer);
  if (!read_result) {
    spdlog::error("could not load configuration");
    return std::nullopt;
  }

  return read_result.value();
}


std::string yumeami::write_config(const ConfigSpec &spec) {
  return rfl::json::write(spec);
}


void yumeami::apply_config_flags(const ConfigSpec &spec) {
  if (spec.vsync) {
    SetWindowState(FLAG_VSYNC_HINT);
  }
}
