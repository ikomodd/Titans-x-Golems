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
    src/game/instances/arena/Arena.cpp
    src/baseplate/data_models/vector/Vector2.cpp
    src/game/instances/character/Character.cpp
    src/game/managers/asset/Asset.cpp
)

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