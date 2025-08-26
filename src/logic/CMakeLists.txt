add_library(logic
  components.hh
  world.hh
)

set_target_properties(logic PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(logic PUBLIC cxx_std_20)
target_include_directories(logic PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)
target_link_libraries(logic PUBLIC
  raylib
  EnTT::EnTT
)
