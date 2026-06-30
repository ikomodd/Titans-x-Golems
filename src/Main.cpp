#include <iostream>

#include "baseplate/manager/Manager.hpp"

#include "game/managers/core/Core.hpp"
#include "game/managers/display/Display.hpp"
#include "game/managers/state/State.hpp"

#include "game/states/main_state/MainState.hpp"

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event Event;

    // Inicia os managers

    GAME_CoreManager& Core = BSPLT_Manager<GAME_CoreManager>::Get();
    GAME_DisplayManager& Display = BSPLT_Manager<GAME_DisplayManager>::Get();
    GAME_StateManager& State = BSPLT_Manager<GAME_StateManager>::Get();

    BSPLT_iManager::InitManagers();

    // Cena inicial

    auto* MainState = new GAME_MainState();
    State.PlayState(MainState);

    // Loop

    while (Core.Running) {
        while (SDL_PollEvent(&Event)) {
            BSPLT_iManager::CallEventManager(Event);
        }

        BSPLT_iManager::ProcessManagers();
    }

    // Fecha

    BSPLT_iManager::CloseManagers();

    SDL_Quit();

    return 1;
}