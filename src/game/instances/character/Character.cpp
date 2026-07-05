#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

#include "game/instances/arena/Arena.hpp"

bool GAME_Character::TileIsInActionDirections(Vector2i tile) {

    auto& CharactionActionDirections = m_ActionDirections;;

    if (std::any_of(CharactionActionDirections.begin(), CharactionActionDirections.end(),
    [this, tile](const Vector2i& A) {

        Vector2i ActionTile = m_TilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

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

    if (!Arena->HasCharacterIn(tile_position)) {

        m_TilePosition = tile_position;
        Position = Vector2(tile_position.X + tile_position.Y, tile_position.Y - tile_position.X) * Arena->GetTileSize();
    }
    else
    Arena->AttackTile(tile_position);
}

void GAME_Character::GetDamage(float damage) {

    std::cout << "ai levei dano\n";
}

//

void GAME_Character::_Ready() {

    BuildCharacter();

    MoveTo(m_SpawnPosition);
}

void GAME_Character::_Draw(SDL_Renderer* renderer) {

    // Renderiza o Character

    Vector2 TextureSize = Vector2(m_Surface->w, m_Surface->h);
    SDL_FRect CharacterRect = {
        Position.X - TextureSize.X / 2,
        Position.Y - TextureSize.Y,
        TextureSize.X,
        TextureSize.Y
    };

    CharacterRect = m_DisplayManager->GetCurrentCamera()->GetRectCameraView(CharacterRect);
    SDL_RenderTexture(renderer, m_Texture, NULL, &CharacterRect);
}