add_library(dbg STATIC
  debug.cc
  debug.hh
)

target_include_directories(dbg PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(dbg PUBLIC
  common
  game
  io
PRIVATE
  ${CORE_EXTERNAL_LIBS}
  ${IO_EXTERNAL_LIBS}
)
