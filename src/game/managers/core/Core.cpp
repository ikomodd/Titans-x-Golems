#include "Core.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void GAME_CoreManager::_Init() {


}

void GAME_CoreManager::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_QUIT)
        Running = false;

    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();

    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();
    for (BSPLT_Node* node : LinearStateChildren) {

        node->_Event(event);
    }
}

void GAME_CoreManager::_Process() {
    
    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();

    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();
    for (BSPLT_Node* node : LinearStateChildren) {

        node->_Process(0.0);
    }
}

void GAME_CoreManager::_Close() {
    
}