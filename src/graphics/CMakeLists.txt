add_library(graphics
  texture.cc
  texture.hh
)

target_compile_features(graphics PUBLIC cxx_std_20)
target_include_directories(graphics PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(graphics PUBLIC
  spdlog
  raylib
)
