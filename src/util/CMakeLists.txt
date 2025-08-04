add_library(util STATIC
  direction.hh
  units.hh
  viewport_transform.cc 
  viewport_transform.hh
)

target_include_directories(util PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(util PUBLIC
  raylib
)
