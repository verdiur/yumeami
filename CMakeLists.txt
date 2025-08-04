cmake_minimum_required(VERSION 3.24...3.30) # C++20

project(
  yumeami
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##########################################################################################
# find packages

include(FetchContent)

# raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)

# entt
FetchContent_Declare(
  EnTT
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.15.0
)
FetchContent_MakeAvailable(EnTT)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)

##########################################################################################
# targets

add_subdirectory(${CMAKE_SOURCE_DIR}/src/game)
add_subdirectory($CMAKE_SOURCE_DIR/src/util)

add_executable(${PROJECT_NAME}
  src/main.cc 
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  game 
  util 
)

##########################################################################################
# copy assets

# copy assets folder into build directory after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory  # copy
    ${CMAKE_SOURCE_DIR}/assets                # from
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets # to
    COMMENT "Copying assets to build directory for ${PROJECT_NAME}..."
)
