#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

namespace game {

    class Arena;
    class DisplayManager;

    class Character : public baseplate::Node2D, private baseplate::AssetData {
    private:

        DisplayManager* m_displayManager = nullptr;

        std::string m_sourcePath;
        
    protected:

        float m_health = 0.f;
        float m_shield = 0.f;

        float m_damage = 0.f;

        int m_actions = 0;
        int m_actionsQuantity = 0;

        int m_attackCost = 0;
        int m_motionCost = 0;

        std::vector<baseplate::Vector2i> m_motionDirections {};
        std::vector<baseplate::Vector2i> m_attackDirections {};

        baseplate::Vector2i m_spawnPosition;
        baseplate::Vector2i m_tilePosition = 0;

    public:

        Character(baseplate::Vector2i tile_position, std::string source_path) : m_spawnPosition(tile_position), m_sourcePath(source_path), baseplate::Node2D("no_name_character", 0, 0) {}
        friend class Arena;

        //

        bool TileIsInMotionDirections(baseplate::Vector2i tile);
        bool TileIsInAttackDirections(baseplate::Vector2i tile);

        void BuildCharacter();

        bool MoveTo(baseplate::Vector2i tile_position, bool free = false);
        bool AttackOn(baseplate::Vector2i tile_position);
        
        void GetDamage(float damage);

        baseplate::Vector2i GetTilePosition() {

            return m_tilePosition;
        }

        //

        void Ready() override;
        void Draw(GLuint vao, glm::mat4 projection) override;
    };
}