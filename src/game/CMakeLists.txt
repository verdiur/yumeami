add_library(game
  world.cc
  world.hh
)

target_compile_features(game PUBLIC cxx_std_20)

target_include_directories(game PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(game PUBLIC
  raylib
  EnTT::EnTT
)
