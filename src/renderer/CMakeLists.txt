add_library(renderer
  draw.cc
  draw.hh
)

set_target_properties(logic PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer PUBLIC cxx_std_20)
target_include_directories(renderer PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(renderer PUBLIC
  graphics
  logic

  raylib
  EnTT::EnTT
)
