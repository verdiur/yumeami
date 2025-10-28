cmake_minimum_required(VERSION 3.10...3.31)

project(
  yumeami
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# packages -------------------------------------------------------------------#

find_package(raylib 5.5 QUIET)
if(NOT raylib_FOUND)
  include(FetchContent)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the examples
  set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the example games
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
  )
  FetchContent_MakeAvailable(raylib)
endif()

find_package(EnTT 3.15.0 QUIET)
if (NOT EnTT_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.15.0
  )
  FetchContent_MakeAvailable(EnTT)
endif()

find_package(spdlog 1.16.0 QUIET)
if(NOT spdlog_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0
  )
  FetchContent_MakeAvailable(spdlog)
endif()

# targets --------------------------------------------------------------------#

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cc)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
)

if(WIN32)
  target_link_options(${PROJECT_NAME} PRIVATE
    -static-libgcc
    -static-libstdc++
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  raylib
  EnTT::EnTT
  spdlog
)
