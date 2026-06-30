#include "Display.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void GAME_DisplayManager::_Init() {

    Window = SDL_CreateWindow("game", 800, 600, NULL);
    Renderer = SDL_CreateRenderer(Window, NULL);
}

void GAME_DisplayManager::_Event(SDL_Event& event) {


}

void GAME_DisplayManager::_Process() {
    
    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();

    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();
    for (BSPLT_Node* node : LinearStateChildren) {

        node->_Draw(Renderer);
    }
}

void GAME_DisplayManager::_Close() {

    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
}