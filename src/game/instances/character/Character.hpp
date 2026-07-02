#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"
#include "game/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2Int.hpp"

class GAME_Character : public BSPLT_Node2D, private GAME_AssetData {
private:
    
    inline static unsigned int m_PrevCharacterId = 0;
    unsigned int m_CharacterId = m_PrevCharacterId++;

    std::string m_SourcePath;

    float m_Health = 0.f;
    float m_Shield = 0.f;

    float m_Damage = 0.f;
    float m_DamageVariation = 0.f;

    std::vector<Vector2i> m_ActionDirections {};
    Vector2i m_TilePosition = 0;

public:

    GAME_Character(Vector2i tile_position, std::string source_path) : m_TilePosition(tile_position), m_SourcePath(source_path), BSPLT_Node2D("no_name_character", 0, 0) {}

    void BuildCharacter();

    void _Ready() override;
    void _Draw(SDL_Renderer* renderer) override;
};