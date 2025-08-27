add_library(assetmgt
  texture.cc
  texture.hh
)

target_compile_features(assetmgt PUBLIC cxx_std_20)
target_include_directories(assetmgt PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(assetmgt PUBLIC
  spdlog
  raylib
)
