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

    auto& Core = baseplate::Manager<game::CoreManager>::Get();
    auto& Display = baseplate::Manager<game::DisplayManager>::Get();
    auto& State = baseplate::Manager<game::StateManager>::Get();

    baseplate::iManager::InitManagers();

    // Inicia Assets

    baseplate::AssetData::CreateTextureAsset("block_texture", "assets/textures/Block.png");
    baseplate::AssetData::CreateTextureAsset("undefined_texture", "assets/textures/UndefinedTexture.png");
    baseplate::AssetData::CreateTextureAsset("character_standart", "assets/textures/CharacterStandart.png");

    baseplate::AssetData::CreateShaderAsset("block_shader",  "assets/shaders/BasicVertex.vert", "assets/shaders/block/BlockShader.frag");
    baseplate::AssetData::CreateShaderAsset("texture_shader", "assets/shaders/BasicVertex.vert", "assets/shaders/texture/TextureShader.frag");
    baseplate::AssetData::CreateShaderAsset("color_shader",   "assets/shaders/BasicVertex.vert", "assets/shaders/color/ColorShader.frag");

    // Cena inicial

    auto* MainState = new GAME_MainState();
    State.PlayState(MainState);

    // Loop

    while (Core.Running) {
        while (SDL_PollEvent(&Event)) {

            baseplate::iManager::CallEventManager(Event);
        }

        baseplate::iManager::ProcessManagers();

        SDL_Delay(10);
    }

    // Fecha

    baseplate::iManager::CloseManagers();

    SDL_Quit();

    return 1;
}