# sandbox, placeholder functions for use in development

add_library(_sandbox
  world.cc
  world.hh
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
