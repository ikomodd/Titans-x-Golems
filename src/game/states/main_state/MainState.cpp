#include "MainState.hpp"

#include "game/instances/arena/Arena.hpp"

void GAME_MainState::_Ready() {

    auto* Arena = new GAME_Arena("resources/json_arenas/Arena1.json");
    AddNode(Arena);
}