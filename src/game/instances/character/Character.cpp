#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "game/managers/asset/Asset.hpp"

//

void GAME_Character::BuildCharacter() {

    GAME_AssetManager& AssetManager = BSPLT_Manager<GAME_AssetManager>::Get();

    std::ifstream File("../" + m_SourcePath);
    nlohmann::json Data = nlohmann::json::parse(File);

    Name = Data["id"];

    m_Health          = Data["health"];
    m_Shield          = Data["shield"];
    m_Damage          = Data["damage"];
    m_DamageVariation = Data["damage_variation"];

    ASSET_TextureAsset* TextureAsset = AssetManager.GetTextureAsset(Data["texture_path"]);
    Texture = TextureAsset->Texture;
    Surface = TextureAsset->Surface;

    for (auto& [key, value] : Data["action_directions"].items()) {

        m_ActionDirections.emplace_back(value[0], value[1]);
    }
}

//

void GAME_Character::_Ready() {

    BuildCharacter();
}

void GAME_Character::_Draw(SDL_Renderer* renderer) {

    Vector2 TextureSize = Vector2(Surface->w, Surface->h);

    SDL_FRect Rect = {
        Position.X, Position.Y,
        TextureSize.X, TextureSize.Y
    };

    SDL_RenderTexture(renderer, Texture, NULL, &Rect);
}