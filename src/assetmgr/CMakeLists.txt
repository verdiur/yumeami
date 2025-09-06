add_library(assetmgr
  texture.cc
  texture.hh
)

target_compile_features(assetmgr PUBLIC cxx_std_20)
target_include_directories(assetmgr PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(assetmgr PUBLIC
  common

  spdlog
  raylib
)
