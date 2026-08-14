cmake_minimum_required(VERSION 3.20)
project(Game CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Game

    src/Main.cpp
    src/game/managers/core/Core.cpp
    src/game/managers/display/Display.cpp
    src/game/managers/scene/Scene.cpp
    src/game/origins/main_scene/MainScene.cpp
    src/game/origins/Origin.cpp
    src/game/instances/arena/Arena.cpp
    src/game/instances/character/Character.cpp
    src/game/instances/character/titan/Titan.cpp
    src/game/instances/camera/Camera.cpp
    src/game/instances/arena/Arena.BFS.cpp
    src/game/managers/interface/Interface.cpp
    src/game/origins/main_ui/MainUi.cpp
    src/game/instances/frame/Frame2D.cpp
    src/game/instances/frame/texture_label/TextureLabel.cpp
    src/game/instances/frame/text_label/TextLabel.cpp
)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(Game PRIVATE

    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    nlohmann_json::nlohmann_json
    glad::glad
    glm::glm
)

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)