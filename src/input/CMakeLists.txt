# input handling

add_library(input
  input.cc
  input.hh
)

target_compile_features(input PUBLIC cxx_std_20)
target_include_directories(input PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(input PUBLIC
  logic

  raylib
  EnTT::EnTT
)
