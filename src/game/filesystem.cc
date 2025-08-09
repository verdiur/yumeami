#include "game/filesystem.hh"
#include "spdlog/spdlog.h"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif

std::optional<std::filesystem::path> yumeami::get_exe_dir() {
  // TODO: implement fully
#ifdef _WIN32
  char buffer[MAX_PATH];
  GetModuleFileNameA(NULL, buffer, MAX_PATH);
  return std::filesystem::path(buffer);

#elif defined(__APPLE__)
  // ???????

#elif defined(__linux__)
  std::string linkPath = "/proc/self/exe";
  char *resolved = realpath(linkPath.c_str(), nullptr);
  if (resolved) {
    std::filesystem::path result = std::filesystem::path(resolved);
    free(resolved);
    return result;
  }
#endif

  // fallback
  spdlog::critical("Cannot get executable directory");
  return std::nullopt;
}
