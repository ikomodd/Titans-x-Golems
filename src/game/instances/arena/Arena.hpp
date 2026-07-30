#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"

namespace game::arena {

    struct Tile {

        baseplate::Vector2 SourcePosition;

        bool Obstacle;

        Tile(baseplate::Vector2 source_position, bool obstacle) : SourcePosition(source_position), Obstacle(obstacle) {}
    };
}

namespace game {

    class DisplayManager;
    class Character;

    class Golem;
    class Titan;

    class Arena : public baseplate::Node2D, private baseplate::AssetData {
    private:

        DisplayManager* mDisplayManager = nullptr;

        unsigned int mCurrentRound = 1;

        bool Builded = false;

        baseplate::Vector2 m_TileSize = 0;
        baseplate::Vector2 m_TileSourceSize = 0;
        baseplate::Vector2 m_TileOffset = 0;

        std::unordered_map<int, arena::Tile*> m_Tileset;
        std::vector<std::pair<baseplate::Vector2i, int>> m_Tilemap;

        std::string m_JsonPath = "";

        Golem* m_CurrentGolem = nullptr;

    public:

        Arena(const char* json_path) : m_JsonPath(json_path), baseplate::Node2D("arena", 0, 0) {}

    private:

        bool TestTileClicked(baseplate::Vector2 click_position, baseplate::Vector2i tile_position);

        void SelectGolem(Golem* golem);
        void UnselectGolem();

        void BuildArena();

        void PlayerRoundEnded();

    public:

        baseplate::Vector2 GetTileSize() {
            return m_TileSize;
        }



        bool CanMoveTo(baseplate::Vector2i tile);

        void AttackTile(baseplate::Vector2i tile, float damage);

        void _Ready() override;
        void _Event(SDL_Event& event) override;
        void _Draw(GLuint vao, glm::mat4 projection) override;
        void _Process(double delta) override;
    };
}