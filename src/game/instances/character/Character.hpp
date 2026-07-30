#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

class GAME_DisplayManager;

class GAME_Arena;

class GAME_Character : public baseplate::Node2D, private baseplate::AssetData {
private:

    GAME_DisplayManager* mDisplayManager = nullptr;

    std::string m_SourcePath;

protected:

    float m_Health = 0.f;
    float m_Shield = 0.f;

    float m_Damage = 0.f;

    unsigned int m_Actions = 0;
    unsigned int m_ActionsQuantity = 0;

    std::vector<baseplate::Vector2i> m_MotionDirections {};
    std::vector<baseplate::Vector2i> m_AttackDirections {};

    baseplate::Vector2i m_SpawnPosition;
    baseplate::Vector2i m_TilePosition = 0;

public:

    GAME_Character(baseplate::Vector2i tile_position, std::string source_path) : m_SpawnPosition(tile_position), m_SourcePath(source_path), baseplate::Node2D("no_name_character", 0, 0) {}
    friend class GAME_Arena;

    //

    bool TileIsInMotionDirections(baseplate::Vector2i tile);
    bool TileIsInAttackDirections(baseplate::Vector2i tile);

    void BuildCharacter();

    void MoveTo(baseplate::Vector2i tile_position);
    void AttackOn(baseplate::Vector2i tile_position);
    
    void GetDamage(float damage);

    baseplate::Vector2i GetTilePosition() {

        return m_TilePosition;
    }

    //

    void _Ready() override;
    void _Draw() override;
};