add_subdirectory(game)
add_subdirectory(util)

add_executable(${PROJECT_NAME}
  main.cc 
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  game 
  util 
)
