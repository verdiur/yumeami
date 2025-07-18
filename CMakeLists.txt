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

##########################################################################################
# targets

# main
add_executable(${PROJECT_NAME}
  src/game/event/base.hh
  src/game/event/input.hh
  src/game/event/input.cc
  src/game/event/simple_events.hh
  src/game/event/simple_queues.hh
  src/game/system/draw.hh
  src/game/system/draw.cc
  src/game/system/movement.hh
  src/game/system/movement.cc
  src/game/simple_components.hh
  src/game/world.hh
  src/game/world.cc

  src/util/display_manager.hh
  src/util/display_manager.cc
  src/util/simple_functions.hh
  src/util/simple_functions.cc
  src/util/simple_types.hh
  src/util/units.hh

  src/main.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE
  src/
)

##########################################################################################
# link

# main
target_link_libraries(${PROJECT_NAME} PRIVATE
  raylib
  EnTT::EnTT
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
