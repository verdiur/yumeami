add_library(game STATIC
  components.hh
  conversions.cc
  conversions.hh
  debug.hh
  debug.cc
  draw.cc
  draw.hh
  input.cc
  input.hh
  movement.cc
  movement.hh
  texture.cc
  texture.hh
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
