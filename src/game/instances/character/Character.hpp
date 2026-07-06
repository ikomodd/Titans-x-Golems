#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"
#include "game/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2Int.hpp"

class GAME_Arena;

class GAME_Character : public BSPLT_Node2D, private GAME_AssetData {
private:

    std::string m_SourcePath;

protected:

    float m_Health = 0.f;
    float m_Shield = 0.f;

    float m_Damage = 0.f;
    float m_DamageVariation = 0.f;

    unsigned int m_CurrentRound = 0;

    std::vector<Vector2i> m_MotionDirections {};
    std::vector<Vector2i> m_AttackDirections {};

    Vector2i m_SpawnPosition;
    Vector2i m_TilePosition = 0;

public:

    GAME_Character(Vector2i tile_position, std::string source_path) : m_SpawnPosition(tile_position), m_SourcePath(source_path), BSPLT_Node2D("no_name_character", 0, 0) {}
    friend class GAME_Arena;

    //

    bool TileIsInMotionDirections(Vector2i tile);
    bool TileIsInAttackDirections(Vector2i tile);

    void BuildCharacter();

    void MoveTo(Vector2i tile_position);
    void AttackOn(Vector2i tile_position);
    
    void GetDamage(float damage);

    //

    void _Ready() override;
    void _Draw(SDL_Renderer* renderer) override;
};