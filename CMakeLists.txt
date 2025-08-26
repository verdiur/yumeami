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

# reflect-cpp
FetchContent_Declare(
  reflectcpp
  GIT_REPOSITORY https://github.com/getml/reflect-cpp.git
  GIT_TAG v0.20.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(reflectcpp)

##########################################################################################
# targets

set(CORE_EXTERNAL_LIBS
  raylib
  EnTT::EnTT
  spdlog
)
set(IO_EXTERNAL_LIBS
  reflectcpp
)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/common)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/game)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/io)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/dbg)

add_executable(${PROJECT_NAME}
  src/main.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  common
  game
  io
  dbg
  ${CORE_EXTERNAL_LIBS}
  ${IO_EXTERNAL_LIBS}
)

##########################################################################################
# copy assets

# copy resource folder into build directory
add_custom_target(copy_res ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory  # copy
    ${CMAKE_SOURCE_DIR}/res                   # from
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/res    # to
    COMMENT "Copying resources to build directory for ${PROJECT_NAME}..."
)
add_dependencies(${PROJECT_NAME} copy_res)
