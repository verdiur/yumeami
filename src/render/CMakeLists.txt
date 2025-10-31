set(LIB_NAME render)
include(sources.cmake)
add_library(${LIB_NAME} ${SOURCES})

target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)
target_include_directories(${LIB_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(${LIB_NAME} PUBLIC
  common
  model

  spdlog
  raylib
  EnTT::EnTT
)
