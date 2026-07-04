#include "MainState.hpp"

#include "game/instances/arena/Arena.hpp"
#include "game/instances/character/Character.hpp"

#include "game/instances/camera/Camera.hpp"

void GAME_MainState::_Ready() {

    auto* Camera = new GAME_Camera("main_camera", Vector2(0.f, 0.f), 1.f, true);
    AddNode(Camera);

    auto* Arena = new GAME_Arena("resources/json_arenas/Arena1.json");
    AddNode(Arena);

    auto* Golem = new GAME_Character(Vector2i(0, 0), "resources/characters/golens/Plague2.json", true);
    Arena->AddNode(Golem);

    auto* Titan = new GAME_Character(Vector2i(7, 7), "resources/characters/golens/Plague2.json", false);
    Arena->AddNode(Titan);
}