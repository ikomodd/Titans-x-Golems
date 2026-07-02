#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "game/managers/display/Display.hpp"
#include "game/instances/camera/Camera.hpp"

#include "game/managers/asset/Asset.hpp"

class GAME_AssetData {
protected:

    GAME_AssetManager* m_AssetManager = nullptr;
    GAME_DisplayManager* m_DisplayManager = nullptr;

    SDL_Texture* m_Texture = nullptr;
    SDL_Surface* m_Surface = nullptr;

    std::string m_SourcePath = "";

public:

    GAME_AssetData() {

        m_AssetManager = &BSPLT_Manager<GAME_AssetManager>::Get();
        m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();
    }

    void LoadTexture(std::string source_path) {

        ASSET_TextureAsset* TextureAsset = m_AssetManager->GetTextureAsset(source_path);
        m_Texture = TextureAsset->Texture;
        m_Surface = TextureAsset->Surface;
    }
};