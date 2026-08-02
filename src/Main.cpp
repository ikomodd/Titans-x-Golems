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
    SDL_Event event;

    // Inicia os managers

    auto& core = baseplate::Manager<game::CoreManager>::Get();
    auto& display = baseplate::Manager<game::DisplayManager>::Get();
    auto& state = baseplate::Manager<game::StateManager>::Get();

    baseplate::iManager::InitManagers();

    // Inicia Assets

    baseplate::AssetData::CreateTextureAsset("block_texture", "assets/textures/Block.png");
    baseplate::AssetData::CreateTextureAsset("undefined_texture", "assets/textures/UndefinedTexture.png");
    baseplate::AssetData::CreateTextureAsset("character_standart", "assets/textures/CharacterStandart.png");

    baseplate::AssetData::CreateShaderAsset("block_shader",  "assets/shaders/BasicVertex.vert", "assets/shaders/block/BlockShader.frag");
    baseplate::AssetData::CreateShaderAsset("texture_shader", "assets/shaders/BasicVertex.vert", "assets/shaders/texture/TextureShader.frag");
    baseplate::AssetData::CreateShaderAsset("color_shader",   "assets/shaders/BasicVertex.vert", "assets/shaders/color/ColorShader.frag");

    // Cena inicial

    auto* mainState = new game::txg::MainState();
    state.PlayState(mainState);

    // Loop

    while (core.running) {
        while (SDL_PollEvent(&event)) {

            baseplate::iManager::CallEventManager(event);
        }

        baseplate::iManager::ProcessManagers();

        SDL_Delay(10);
    }

    // Fecha

    baseplate::iManager::CloseManagers();

    SDL_Quit();

    return 1;
}