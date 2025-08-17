#pragma once

#include <optional>
#include <string>
namespace yumeami {

  struct ConfigSpec {
    const int window_width = 640 * 2;  // width of application window
    const int window_height = 480 * 2; // height of application window
    const int viewport_width = 640;    // width of game viewport
    const int viewport_height = 480;   // height of game_viewport

    bool vsync = true; // vsync flag
  };

  /**
   * @brief Parse config from JSON string buffer
   * @param buffer
   */
  std::optional<ConfigSpec> parse_config(std::string buffer);

  /**
   * @brief Generate JSON string from config spec
   *
   * @param spec
   */
  std::string write_config(const ConfigSpec &spec);

  /**
   * @brief Apply configuration flags from config spec instance
   * @param spec
   */
  void apply_config_flags(const ConfigSpec &spec);

} // namespace yumeami
