# sandbox, placeholder functions for use in development

add_library(_sandbox
  ai_random_move.cc
  animation.cc
  background.cc
  clamp.cc
  collision.cc
  decl.hh
  position.cc
  spritesheet.cc
  wrap.cc
  zorder.cc
)

target_compile_features(_sandbox PUBLIC cxx_std_20)
target_include_directories(_sandbox PRIVATE
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(_sandbox PUBLIC
  ai
  logic
  resman

  raylib
  spdlog
)
