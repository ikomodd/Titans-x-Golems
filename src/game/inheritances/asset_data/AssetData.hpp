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

    ASSET_ShaderAsset* m_ShaderAsset;
    ASSET_TextureAsset* m_TextureAsset;

    std::string m_SourcePath = "";

public:

    GAME_AssetData() {

        m_AssetManager = &BSPLT_Manager<GAME_AssetManager>::Get();
        m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();
    }

    void LoadTexture(std::string source_path) {

        m_TextureAsset = m_AssetManager->GetTextureAsset(source_path);
    }

    void LoadShader(std::string vertex_path, std::string fragment_path) {

        m_ShaderAsset = m_AssetManager->GetShaderAsset(vertex_path, fragment_path);
    }
};