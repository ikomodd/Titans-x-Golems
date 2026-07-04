#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "baseplate/manager/Manager.hpp"

#include "game/managers/core/Core.hpp"
#include "game/managers/display/Display.hpp"
#include "game/managers/state/State.hpp"
#include "game/managers/asset/Asset.hpp"

#include "game/states/main_state/MainState.hpp"

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event Event;

    // Inicia os managers

    GAME_CoreManager& Core = BSPLT_Manager<GAME_CoreManager>::Get();
    GAME_DisplayManager& Display = BSPLT_Manager<GAME_DisplayManager>::Get();
    GAME_StateManager& State = BSPLT_Manager<GAME_StateManager>::Get();
    GAME_AssetManager& Asset = BSPLT_Manager<GAME_AssetManager>::Get();

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

        SDL_Delay(10);
    }

    // Fecha

    BSPLT_iManager::CloseManagers();

    SDL_Quit();

    return 1;
}