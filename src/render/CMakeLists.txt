# render functions

add_library(render
  draw_debug.cc
  draw_debug.hh
  draw_sprites.cc
  draw_sprites.hh
  draw_world.cc
  draw_world.hh
)

target_compile_features(render PUBLIC cxx_std_20)
target_include_directories(render PRIVATE
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(render PUBLIC
  resman
  logic

  raylib
)
