add_library(test
  test_worlds.cc
  test_worlds.hh
)

target_compile_features(test PUBLIC cxx_std_20)
target_include_directories(test PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(test PUBLIC
  assetmgt
  common
  logic
  render

  raylib
  EnTT::EnTT
)
