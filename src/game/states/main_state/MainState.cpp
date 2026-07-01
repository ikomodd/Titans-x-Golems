#include "MainState.hpp"

#include "game/instances/arena/Arena.hpp"
#include "game/instances/camera/Camera.hpp"

void GAME_MainState::_Ready() {

    auto* Camera = new GAME_Camera("main_camera", Vector2(0.f, 0.f), 1.f, true);
    AddNode(Camera);

    auto* Arena = new GAME_Arena("resources/json_arenas/Arena1.json");
    AddNode(Arena);
}