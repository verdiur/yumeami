cmake_minimum_required(VERSION 3.10...3.31)

project(yumeami
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

# packages -------------------------------------------------------------------#

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the example games
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  EnTT
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.15.0
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  reflectcpp
  GIT_REPOSITORY https://github.com/getml/reflect-cpp.git
  GIT_TAG v0.20.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(reflectcpp)

# targets --------------------------------------------------------------------#

add_subdirectory(${CMAKE_SOURCE_DIR}/src/common/)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/game/)

add_executable(${PROJECT_NAME}
  src/main.cc
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  common
  game

  raylib
  EnTT::EnTT
)

# resources ------------------------------------------------------------------#

add_custom_target(resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/resources/
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/
  COMMENT "Copying resources/ to build/ for ${PROJECT_NAME}..."
)
add_dependencies(${PROJECT_NAME} resources)
