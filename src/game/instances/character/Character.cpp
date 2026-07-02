#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "game/instances/arena/Arena.hpp"

void GAME_Character::BuildCharacter() {

    std::ifstream File("../" + m_SourcePath);
    nlohmann::json Data = nlohmann::json::parse(File);

    Name = Data["id"];

    m_Health          = Data["health"];
    m_Shield          = Data["shield"];
    m_Damage          = Data["damage"];
    m_DamageVariation = Data["damage_variation"];

    LoadTexture(Data["texture_path"]);

    for (auto& [key, value] : Data["action_directions"].items()) {

        m_ActionDirections.emplace_back(value[0], value[1]);
    }
}

void GAME_Character::MoveTo(Vector2i tile_position) {

    GAME_Arena* Arena = GetParent<GAME_Arena>();

    m_TilePosition = tile_position;
    Position = tile_position.ToVector2() * Arena->GetTileSize();
}

//

void GAME_Character::_Ready() {

    BuildCharacter();

    MoveTo(Vector2i(0, 0));
}

void GAME_Character::_Draw(SDL_Renderer* renderer) {

    Vector2 TextureSize = Vector2(m_Surface->w, m_Surface->h);

    SDL_FRect Rect = {
        Position.X - TextureSize.X / 2,
        Position.Y - TextureSize.Y,
        TextureSize.X,
        TextureSize.Y
    };

    Rect = m_DisplayManager->GetCurrentCamera()->GetRectCameraView(Rect);

    SDL_RenderTexture(renderer, m_Texture, NULL, &Rect);
}