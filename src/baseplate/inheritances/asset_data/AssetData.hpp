#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

#include "baseplate/data_models/color/Color4.hpp"
#include "baseplate/data_models/color/Color4Float.hpp"

#include "game/managers/display/Display.hpp"
#include "game/instances/camera/Camera.hpp"

#include "AssetData.Models.hpp"

class BSPLT_AssetData {
private:

    inline static std::unordered_map<std::string, ASSET_AssetModel*> m_LoadedAssets;

protected:

    GAME_DisplayManager* m_DisplayManager = nullptr;

    ASSET_ShaderAsset* m_ShaderAsset;
    ASSET_TextureAsset* m_TextureAsset;

public:

    Color4 BackgroundColor = Color4::TRANSPARENT;

    BSPLT_AssetData() {

        m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();
    }

    //

    static void CreateTextureAsset(std::string texture_name, std::string texture_path) {

        if (m_LoadedAssets.find(texture_name) == m_LoadedAssets.end()) {

            auto* TextureAsset = new ASSET_TextureAsset(texture_path);
            m_LoadedAssets[texture_name] = TextureAsset;
        }
        else
            std::cerr << "[BSPLT_AssetData] ja existe um asset chamado: " << texture_name << "\n";
    }

    static void CreateShaderAsset(std::string shader_name, std::string vertex_source, std::string fragment_source) {

        if (m_LoadedAssets.find(shader_name) == m_LoadedAssets.end()) {

            auto* ShaderAsset = new ASSET_ShaderAsset(vertex_source, fragment_source);
            m_LoadedAssets[shader_name] = ShaderAsset;
        }
        else
            std::cerr << "[BSPLT_AssetData] Ja existe um asset chamado: " << shader_name << "\n";
    }

    void DefineTextureAsset(std::string texture_name) {

        if (m_LoadedAssets.find(texture_name) != m_LoadedAssets.end()) {

            m_TextureAsset = static_cast<ASSET_TextureAsset*>(m_LoadedAssets[texture_name]);
        }
        else if (m_LoadedAssets.find("undefined_texture") != m_LoadedAssets.end())
            DefineTextureAsset("undefined_texture");
        else
            std::cerr << "[BSPLT_AssetData] Textura: " << texture_name << " nao esta definido e nao ha nenhuma textura de depuraçao\n";
    }

    void DefineShaderAsset(std::string shader_name) {

        if (m_LoadedAssets.find(shader_name) != m_LoadedAssets.end()) {

            m_ShaderAsset = static_cast<ASSET_ShaderAsset*>(m_LoadedAssets[shader_name]);
        }
        else
            std::cerr << "[BSPLT_AssetData] Shader: " << shader_name << " nao esta definido\n";
    }
};