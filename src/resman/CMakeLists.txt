# resource manager

add_library(resman
  texture.cc
  texture.hh
)

target_compile_features(resman PUBLIC cxx_std_20)
target_include_directories(resman PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(resman PUBLIC
  common

  spdlog
  raylib
)
