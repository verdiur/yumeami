# asset manager

add_library(assman
  texture.cc
  texture.hh
)

target_compile_features(assman PUBLIC cxx_std_20)
target_include_directories(assman PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(assman PUBLIC
  common

  spdlog
  raylib
)
