/**
 * @file config_io.hh
 * @brief Configuration I/O
 */

#pragma once

#include "rfl/Description.hpp"
#include <filesystem>
#include <optional>

namespace yumeami {

  struct ConfigSpec { // clang-format off
    rfl::Description<
      "Width of application window",
      int> window_width = 640 * 2;
    rfl::Description<
      "Height of application window",
      int> window_height = 480 * 2;
    const rfl::Description<
      "Width of viewport. Changing this option will mess up the graphics.",
      int> viewport_width = 640;
    const rfl::Description<
      "Height of viewport. Changing this option will mess up the graphics.",
      int> viewport_height = 480;
    rfl::Description<
      "VSync flag",
      bool> vsync = true;
  }; // clang-format on

  /**
   * @brief Parse config from JSON string buffer
   * @param buffer
   */
  std::optional<ConfigSpec> parse_config(std::filesystem::path cfg_path);

  /**
   * @brief Write config spec to file
   *
   * @param spec
   * @param cfg_path
   */
  void write_config(const ConfigSpec &spec, std::filesystem::path cfg_path);

  /**
   * @brief Apply configuration flags from config spec instance
   * @param spec
   */
  void load_config(const ConfigSpec &spec);

} // namespace yumeami
