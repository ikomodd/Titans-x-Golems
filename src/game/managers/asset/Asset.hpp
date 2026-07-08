#include "baseplate/manager/Manager.hpp"

#include <unordered_map>

#include "Asset.AssetModels.hpp"

class GAME_AssetManager : public BSPLT_Manager<GAME_AssetManager> {
private:

    GAME_AssetManager() : BSPLT_Manager<GAME_AssetManager>("asset_manager") {}
    friend class BSPLT_Manager<GAME_AssetManager>;

    std::unordered_map<std::string, ASSET_TextureAsset*> m_LoadedTextures;
    std::unordered_map<std::string, ASSET_ShaderAsset*> m_LoadedShaders;

public:

    ASSET_TextureAsset* GetTextureAsset(std::string path);
    ASSET_ShaderAsset* GetShaderAsset(std::string vertex_path, std::string fragment_path);
};