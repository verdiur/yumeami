# game logic

add_library(logic
  camera.cc
  camera.hh
  collision.cc
  collision.hh
  components.hh
  components_op.cc
  components_op.hh
  emplace.cc
  emplace.hh
  movement.cc
  movement.hh
  world.cc
  world.hh
)

target_compile_features(logic PUBLIC cxx_std_20)
target_include_directories(logic PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(logic PUBLIC
  raylib
  EnTT::EnTT
  spdlog
)
