#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "baseplate/manager/Manager.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

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

    // Inicia Assets

    BSPLT_AssetData::CreateTextureAsset("block_texture", "assets/textures/Block.png");
    BSPLT_AssetData::CreateTextureAsset("undefined_texture", "assets/textures/UndefinedTexture.png");

    BSPLT_AssetData::CreateShaderAsset("block_shader",  "assets/shaders/BasicVertex.vert", "assets/shaders/block/BlockShader.frag");
    BSPLT_AssetData::CreateShaderAsset("texture_shader", "assets/shaders/BasicVertex.vert", "assets/shaders/texture/TextureShader.frag");
    BSPLT_AssetData::CreateShaderAsset("color_shader",   "assets/shaders/BasicVertex.vert", "assets/shaders/color/ColorShader.frag");

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