#pragma once

#include <unordered_map>

#include "baseplate/data_models/color/Color4.hpp"
#include "baseplate/data_models/model/RenderModel.hpp"

#include "AssetData.Models.hpp"

namespace baseplate {

    class AssetData {
    private:

        inline static std::unordered_map<std::string, asset::AssetModel*> m_loadedAssets;

    protected:

        asset::ShaderAsset* m_shaderAsset = nullptr;
        asset::TextureAsset* m_textureAsset = nullptr;
        asset::FontAsset* m_fontAsset = nullptr;

    public:

        baseplate::Color4 backgroundColor = baseplate::ColorPressets::TRANSPARENT;

        AssetData() {}
        ~AssetData() {

            if (m_textureAsset->isDynamic)
                delete m_textureAsset;
        }

        // Get

        bool HasTexture() {

            return m_textureAsset;
        }

        // ---------------------------------------------------------------------------------

        // Cria um Asset de textura

        static void CreateTextureAsset(std::string texture_name, std::string texture_path) {

            if (m_loadedAssets.find(texture_name) == m_loadedAssets.end()) {

                auto* textureAsset = new asset::TextureAsset(texture_path);
                m_loadedAssets[texture_name] = textureAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] ja existe um asset chamado: " << texture_name << "\n";
        }

        // Cria um Asset de shader

        static void CreateShaderAsset(std::string shader_name, std::string vertex_source, std::string fragment_source) {

            if (m_loadedAssets.find(shader_name) == m_loadedAssets.end()) {

                auto* shaderAsset = new asset::ShaderAsset(vertex_source, fragment_source);
                m_loadedAssets[shader_name] = shaderAsset;
            }
            else
                std::cerr << "[baseplate::AssetData] Ja existe um asset chamado: " << shader_name << "\n";
        }

        // Cria um Asset de fonte

        static void CreateFontAsset(std::string font_name, std::string font_path, float font_size) {

            if (m_loadedAssets.find(font_name) == m_loadedAssets.end()) {

                auto* fontAsset = new asset::FontAsset(font_path, font_size);
                m_loadedAssets[font_name] = fontAsset;
            }
            else
                std::cerr << "[baseplate::assetData] Ja existe um asset chamado: " << font_name << "\n";
        }

        // Pega uma textura da lista para si próprio

        void DefineTextureAsset(std::string texture_name) {

            if (m_loadedAssets.find(texture_name) != m_loadedAssets.end())

                m_textureAsset = static_cast<asset::TextureAsset*>(m_loadedAssets[texture_name]);

            else if (m_loadedAssets.find("undefined_texture") != m_loadedAssets.end())

                DefineTextureAsset("undefined_texture");
            else
                std::cerr << "[baseplate::AssetData] Textura: " << texture_name << " nao esta definido e nao ha nenhuma textura de depuraçao\n";
        }

        // Pega um shader da lista para si próprio

        void DefineShaderAsset(std::string shader_name) {

            if (m_loadedAssets.find(shader_name) != m_loadedAssets.end())

                m_shaderAsset = static_cast<asset::ShaderAsset*>(m_loadedAssets[shader_name]);
            else
                std::cerr << "[baseplate::AssetData] Shader: " << shader_name << " nao esta definido\n";
        }
    
        // Pega uma fonte da lista para si proprio

        void DefineFontAsset(std::string font_name) {

            if (m_loadedAssets.find(font_name) != m_loadedAssets.end())

                m_fontAsset = static_cast<asset::FontAsset*>(m_loadedAssets[font_name]);
            else
                std::cerr << "[baseplate::AssetData] Font: " << font_name << " nao esta definido\n";
        }

        // Cria uma asset único para um texto

        void RenderText(std::string text, Color4 text_color) {

            if (m_fontAsset) {

                if (m_textureAsset && m_textureAsset->isDynamic)
                    delete m_textureAsset;

                m_textureAsset = new asset::TextureAsset(text, text_color, m_fontAsset->font);
            }
            else
                std::cerr << "[baseplate::AssetData] Nao e possivel renderizar texto: " << text << " sem ter um asset de fonte definido\n";
        }
    };
}