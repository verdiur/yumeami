add_library(io STATIC
  config_io.cc
  config_io.hh
  world_io.cc
  world_io.hh
)

target_compile_features(io PUBLIC cxx_std_20)

target_include_directories(io PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(io PUBLIC
  game
PRIVATE
  ${CORE_EXTERNAL_LIBS}
  ${IO_EXTERNAL_LIBS}
)
