#include "baseplate/manager/Manager.hpp"

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "game/managers/display/Display.hpp"

struct ASSET_TextureAsset {

    SDL_Texture* Texture;
    SDL_Surface* Surface;

    ASSET_TextureAsset(SDL_Renderer* renderer, std::string texture_path) {

        std::string FullPath = "../" + texture_path;
        Surface = IMG_Load(FullPath.c_str());

        if (!Surface)
            std::cerr << "[ASSET_TextureAsset] Nao foi possivel carregar a textura: " << texture_path << ": \n" << SDL_GetError() << "\n";

        Texture = SDL_CreateTextureFromSurface(renderer, Surface);
    }
};

class GAME_AssetManager : public BSPLT_Manager<GAME_AssetManager> {
private:

    GAME_AssetManager() : BSPLT_Manager<GAME_AssetManager>("asset_manager") {}
    friend class BSPLT_Manager<GAME_AssetManager>;

    std::unordered_map<std::string, ASSET_TextureAsset*> m_LoadedTextures;

public:

    ASSET_TextureAsset* GetTextureAsset(std::string path) {
        auto it = m_LoadedTextures.find(path);

        if (it != m_LoadedTextures.end())
            return it->second;

        else {
            GAME_DisplayManager& DisplayManager = BSPLT_Manager<GAME_DisplayManager>::Get();

            m_LoadedTextures[path] = new ASSET_TextureAsset(DisplayManager.Renderer, path);
            return m_LoadedTextures[path];
        }
    }
};