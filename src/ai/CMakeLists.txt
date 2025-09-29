# npc AI, action-taking

add_library(ai
  base.cc
  base.hh
  death.cc
  death.hh
  idle.cc
  idle.hh
  move_random.cc
  move_random.hh
)

target_compile_features(ai PUBLIC cxx_std_20)
target_include_directories(ai PRIVATE
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(ai PUBLIC
  logic
  spdlog
)
