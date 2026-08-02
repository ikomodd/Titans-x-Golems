#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

#include "baseplate/data_models/color/Color4.hpp"

#include "AssetData.Models.hpp"

namespace baseplate {

    class AssetData {
    private:

        inline static std::unordered_map<std::string, asset::AssetModel*> m_loadedAssets;

    protected:

        asset::ShaderAsset* m_shaderAsset;
        asset::TextureAsset* m_textureAsset;

    public:

        baseplate::Color4 backgroundColor = baseplate::ColorPressets::TRANSPARENT;

        // Cria um Asset de textura

        static void CreateTextureAsset(std::string texture_name, std::string texture_path) {

            if (m_loadedAssets.find(texture_name) == m_loadedAssets.end()) {

                auto* textureAsset = new asset::TextureAsset(texture_path);
                m_loadedAssets[texture_name] = textureAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] ja existe um asset chamado: " << texture_name << "\n";
        }

        // Cria um Asset de Shader

        static void CreateShaderAsset(std::string shader_name, std::string vertex_source, std::string fragment_source) {

            if (m_loadedAssets.find(shader_name) == m_loadedAssets.end()) {

                auto* shaderAsset = new asset::ShaderAsset(vertex_source, fragment_source);
                m_loadedAssets[shader_name] = shaderAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] Ja existe um asset chamado: " << shader_name << "\n";
        }

        // Pega uma textura da lista para si próprio

        void DefineTextureAsset(std::string texture_name) {

            if (m_loadedAssets.find(texture_name) != m_loadedAssets.end()) {

                m_textureAsset = static_cast<asset::TextureAsset*>(m_loadedAssets[texture_name]);
            }
            else if (m_loadedAssets.find("undefined_texture") != m_loadedAssets.end())
                DefineTextureAsset("undefined_texture");
            else
                std::cerr << "[baseplate::AssetData] Textura: " << texture_name << " nao esta definido e nao ha nenhuma textura de depuraçao\n";
        }

        void DefineShaderAsset(std::string shader_name) {

            if (m_loadedAssets.find(shader_name) != m_loadedAssets.end()) {

                m_shaderAsset = static_cast<asset::ShaderAsset*>(m_loadedAssets[shader_name]);
            }
            else
                std::cerr << "[baseplate::AssetData] Shader: " << shader_name << " nao esta definido\n";
        }
    };
}