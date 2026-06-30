cmake_minimum_required(VERSION 3.20)
project(Game CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Game

    src/Main.cpp
    src/game/managers/core/Core.cpp
    src/game/managers/display/Display.cpp
    src/game/managers/state/State.cpp
    src/baseplate/inheritances/children/Children.cpp
    src/game/states/main_state/MainState.cpp
    src/game/states/state/State.cpp
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(Game PRIVATE SDL3::SDL3)

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)