add_library(game STATIC
  components.hh
  draw.cc
  draw.hh
  movement.cc 
  movement.hh
  world.cc 
  world.hh
)

target_include_directories(game PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(game PUBLIC
  util
  raylib
  EnTT::EnTT 
  spdlog::spdlog 
)
