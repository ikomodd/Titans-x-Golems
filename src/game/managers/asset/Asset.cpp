#include "Asset.hpp"

ASSET_TextureAsset* GAME_AssetManager::GetTextureAsset(std::string path) {

    if (path.empty()) {
        std::cout << "[GAME_AssetManager] Solicitacao de asset vazia recebida\n";
        return GetTextureAsset("assets/NoTextureResource.png");
    }

    auto it = m_LoadedTextures.find(path);

    if (it != m_LoadedTextures.end())
        return it->second;

    else {

        m_LoadedTextures[path] = new ASSET_TextureAsset(path);
        return m_LoadedTextures[path];
    }
    return nullptr;
}

ASSET_ShaderAsset* GAME_AssetManager::GetShaderAsset(std::string vertex_path, std::string fragment_path) {

    std::string ShaderName = vertex_path + fragment_path;

    auto it = m_LoadedShaders.find(ShaderName);

    if (it != m_LoadedShaders.end()) {

        return it->second;
    }
    else {

        m_LoadedShaders[ShaderName] = new ASSET_ShaderAsset(vertex_path, fragment_path);
        return m_LoadedShaders[ShaderName];
    }
}
