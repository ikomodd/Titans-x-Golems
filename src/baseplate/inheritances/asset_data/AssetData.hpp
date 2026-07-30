#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

#include "baseplate/data_models/color/Color4.hpp"

#include "AssetData.Models.hpp"

namespace baseplate {

    class AssetData {
    private:

        inline static std::unordered_map<std::string, asset::AssetModel*> mLoadedAssets;

    protected:

        asset::ShaderAsset* mShaderAsset;
        asset::TextureAsset* mTextureAsset;

    public:

        baseplate::Color4 BackgroundColor = baseplate::ColorPressets::TRANSPARENT;

        // Cria um Asset de textura

        static void CreateTextureAsset(std::string texture_name, std::string texture_path) {

            if (mLoadedAssets.find(texture_name) == mLoadedAssets.end()) {

                auto* TextureAsset = new asset::TextureAsset(texture_path);
                mLoadedAssets[texture_name] = TextureAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] ja existe um asset chamado: " << texture_name << "\n";
        }

        // Cria um Asset de Shader

        static void CreateShaderAsset(std::string shader_name, std::string vertex_source, std::string fragment_source) {

            if (mLoadedAssets.find(shader_name) == mLoadedAssets.end()) {

                auto* ShaderAsset = new asset::ShaderAsset(vertex_source, fragment_source);
                mLoadedAssets[shader_name] = ShaderAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] Ja existe um asset chamado: " << shader_name << "\n";
        }

        // Pega uma textura da lista para si próprio

        void DefineTextureAsset(std::string texture_name) {

            if (mLoadedAssets.find(texture_name) != mLoadedAssets.end()) {

                mTextureAsset = static_cast<asset::TextureAsset*>(mLoadedAssets[texture_name]);
            }
            else if (mLoadedAssets.find("undefined_texture") != mLoadedAssets.end())
                DefineTextureAsset("undefined_texture");
            else
                std::cerr << "[baseplate::AssetData] Textura: " << texture_name << " nao esta definido e nao ha nenhuma textura de depuraçao\n";
        }

        void DefineShaderAsset(std::string shader_name) {

            if (mLoadedAssets.find(shader_name) != mLoadedAssets.end()) {

                mShaderAsset = static_cast<asset::ShaderAsset*>(mLoadedAssets[shader_name]);
            }
            else
                std::cerr << "[baseplate::AssetData] Shader: " << shader_name << " nao esta definido\n";
        }
    };
}