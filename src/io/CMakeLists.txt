add_library(io STATIC
  io.cc
  io.hh
)

target_include_directories(io PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(io PUBLIC
  game
PRIVATE
  ${CORE_EXTERNAL_LIBS}
  ${IO_EXTERNAL_LIBS}
)
