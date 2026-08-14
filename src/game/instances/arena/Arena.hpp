#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "game/instances/node2d/Node2D.hpp"
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

    class TextLabel;

    class Arena : public Node2D, private baseplate::AssetData {
    private:

        using Vector2 = baseplate::Vector2;
        using Vector2i = baseplate::Vector2i;

        DisplayManager* m_displayManager = nullptr;

        unsigned int m_currentRound = 1;

        bool m_builded = false;

        Vector2 m_tileSize = 0;
        Vector2 m_tileSourceSize = 0;
        Vector2 m_tileOffset = 0;

        Vector2i m_mapSize = 0;

        std::unordered_map<int, arena::Tile*> m_tileset;
        std::vector<std::pair<Vector2i, int>> m_tilemap;

        std::string m_jsonPath = "";

        Titan* m_titanInMouseTarget = nullptr;
        Golem* m_currentGolem = nullptr;

        TextLabel* m_roundDisplay = nullptr;

    public:
        
        Arena(const char* json_path) : m_jsonPath(json_path), Node2D("arena", 0, 0) {}

    private:

        bool TestTileClicked(Vector2 click_position, Vector2i tile_position);

        void SelectGolem(Golem* golem);
        void UnselectGolem();

        void BuildArena();

        void PlayerRoundEnded();

    public:

        // Get

        Vector2 GetTileSize() {
            return m_tileSize;
        }

        std::vector<std::pair<Vector2i, int>> GetMap() {

            return m_tilemap;
        }

        //

        void AttackTile(Vector2i tile, float damage);
        bool IsAValidTile(Vector2i tile, bool ignore_characters = false);
        std::vector<Vector2i> MakeBFS(Character* character, Vector2i origin, Vector2i target);

        //

        void Ready() override;
        void Event(const SDL_Event& event) override;
        void Draw(GLuint vao, ::glm::mat4 projection) override;
        void Process(double delta) override;
    };
}