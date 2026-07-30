cmake_minimum_required(VERSION 3.20)
project(Game CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Game

    src/Main.cpp
    src/game/managers/core/Core.cpp
    src/game/managers/display/Display.cpp
    src/game/managers/state/State.cpp
    src/game/states/main_state/MainState.cpp
    src/game/states/state/State.cpp
    src/game/instances/arena/Arena.cpp
    src/game/instances/character/Character.cpp
    src/game/instances/character/titan/Titan.cpp
    src/game/instances/health_bar/HealthBar.cpp
    src/game/instances/camera/Camera.cpp
)

# LEMBRA DE TIRAR ISSO E O "clang_rt.asan_dynamic-x86_64.dll" DO BUILD!!!!!!!!!!!!!!
#target_compile_options(Game PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
#target_link_options(Game PRIVATE -fsanitize=address,undefined)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(Game PRIVATE

    SDL3::SDL3
    SDL3_image::SDL3_image
    nlohmann_json::nlohmann_json
    glad::glad
    glm::glm
)

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)