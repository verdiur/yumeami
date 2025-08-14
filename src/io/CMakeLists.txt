add_library(io STATIC
  io.cc
)

target_include_directories(io PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(io PUBLIC
  game
)
