#include "MainState.hpp"

#include "game/instances/arena/Arena.hpp"

#include "game/instances/character/golem/Golem.hpp"
#include "game/instances/character/titan/Titan.hpp"

#include "game/instances/camera/Camera.hpp"

void GAME_MainState::_Ready() {

    auto* Camera = new GAME_Camera("main_camera", Vector2(0.f, 0.f), 1.f, true);
    AddNode(Camera);

    auto* Arena = new GAME_Arena("resources/arenas/Arena1.json");
    AddNode(Arena);
}