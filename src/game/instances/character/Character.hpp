#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

namespace game {

    class Arena;

    class DisplayManager;

    class Character : public baseplate::Node2D, private baseplate::AssetData {
    private:

        DisplayManager* mDisplayManager = nullptr;

        std::string mSourcePath;

    protected:

        float mHealth = 0.f;
        float mShield = 0.f;

        float mDamage = 0.f;

        unsigned int mActions = 0;
        unsigned int mActionsQuantity = 0;

        std::vector<baseplate::Vector2i> mMotionDirections {};
        std::vector<baseplate::Vector2i> mAttackDirections {};

        baseplate::Vector2i mSpawnPosition;
        baseplate::Vector2i mTilePosition = 0;

    public:

        Character(baseplate::Vector2i tile_position, std::string source_path) : mSpawnPosition(tile_position), mSourcePath(source_path), baseplate::Node2D("no_name_character", 0, 0) {}
        friend class Arena;

        //

        bool TileIsInMotionDirections(baseplate::Vector2i tile);
        bool TileIsInAttackDirections(baseplate::Vector2i tile);

        void BuildCharacter();

        void MoveTo(baseplate::Vector2i tile_position);
        void AttackOn(baseplate::Vector2i tile_position);
        
        void GetDamage(float damage);

        baseplate::Vector2i GetTilePosition() {

            return mTilePosition;
        }

        //

        void _Ready() override;
        void _Draw(GLuint vao, glm::mat4 projection) override;
    };
}