#include "Display.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

#include "baseplate/data_models/vector/Vector2Int.hpp"

void GAME_DisplayManager::SetWindowSize() {

    Vector2i WindowSizeInt = 0;
    SDL_GetWindowSize(Window, &WindowSizeInt.X, &WindowSizeInt.Y);
    m_WindowSize = WindowSizeInt.ToVector2();
}

//

void GAME_DisplayManager::_Init() {

    Window = SDL_CreateWindow("game", 800, 600, SDL_WINDOW_RESIZABLE);
    Renderer = SDL_CreateRenderer(Window, NULL);

    SetWindowSize();
}

void GAME_DisplayManager::_Event(SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED)
        SetWindowSize();
}

void GAME_DisplayManager::_Process() {
    
    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();
    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Renderer);

    for (BSPLT_Node* node : LinearStateChildren) {

        node->_Draw(Renderer);
    }

    SDL_RenderPresent(Renderer);
}

void GAME_DisplayManager::_Close() {

    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
}