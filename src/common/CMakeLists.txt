add_library(common
  direction.hh
  raii.cc
  raii.hh
  units.hh
  viewport_transform.cc
  viewport_transform.hh
)

target_compile_features(common PUBLIC cxx_std_20)
target_include_directories(common PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(common PUBLIC
  raylib
  spdlog
)
