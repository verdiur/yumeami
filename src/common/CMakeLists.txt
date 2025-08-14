add_library(common STATIC
  direction.hh
  units.hh
  viewport_transform.cc 
  viewport_transform.hh
)

target_include_directories(common PUBLIC
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(common PUBLIC
  raylib
)
