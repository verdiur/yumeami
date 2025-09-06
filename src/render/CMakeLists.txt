# render functions

add_library(render
  draw.cc
  draw.hh
)

target_compile_features(render PUBLIC cxx_std_20)
target_include_directories(render PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(render PUBLIC
  assman
  logic

  raylib
  EnTT::EnTT
)
