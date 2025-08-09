#pragma once
#include <filesystem>
#include <optional>

namespace yumeami {

  /**
   * @brief Get executable directory.
   * @warning This function is platform dependent and will only work with win32, linux and
   * darwin.
   */
  std::optional<std::filesystem::path> get_exe_dir();

} // namespace yumeami
