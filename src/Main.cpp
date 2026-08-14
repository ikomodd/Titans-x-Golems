#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "baseplate/manager/Manager.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

#include "game/managers/core/Core.hpp"
#include "game/managers/display/Display.hpp"
#include "game/managers/scene/Scene.hpp"
#include "game/managers/interface/Interface.hpp"

#include "game/origins/main_scene/MainScene.hpp"
#include "game/origins/main_ui/MainUi.hpp"

int main() {

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Event event;

    // Inicia os managers

    auto& core = baseplate::Manager<game::CoreManager>::Get();
    auto& display = baseplate::Manager<game::DisplayManager>::Get();
    auto& interface = baseplate::Manager<game::InterfaceManager>::Get();
    auto& scene = baseplate::Manager<game::SceneManager>::Get();

    baseplate::iManager::InitManagers();

    // Inicia Assets

    baseplate::AssetData::CreateTextureAsset("block_texture", "assets/textures/Block.png");
    baseplate::AssetData::CreateTextureAsset("undefined_texture", "assets/textures/UndefinedTexture.png");
    baseplate::AssetData::CreateTextureAsset("character_standart", "assets/textures/CharacterStandart.png");

    baseplate::AssetData::CreateShaderAsset("block_shader",  "assets/shaders/BasicVertex.vert", "assets/shaders/block/BlockShader.frag");
    baseplate::AssetData::CreateShaderAsset("texture_shader", "assets/shaders/BasicVertex.vert", "assets/shaders/texture/TextureShader.frag");
    baseplate::AssetData::CreateShaderAsset("color_shader",   "assets/shaders/BasicVertex.vert", "assets/shaders/color/ColorShader.frag");

    baseplate::AssetData::CreateFontAsset("jacquard_12", "assets/fonts/jacquard12/Jacquard12-Regular.ttf", 48.f);
    baseplate::AssetData::CreateFontAsset("geist_pixel", "assets/fonts/geist_pixel/GeistPixel-Regular-VariableFont_ELSH.ttf", 32.f);

    // Interface inicial

    auto* MainUi = new game::MainUi();
    interface.PlayInterface(MainUi);

    // Cena inicial

    auto* mainScene = new game::MainScene();
    scene.PlayScene(mainScene);

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