#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"

class GAME_DisplayManager;

class GAME_Character;
class GAME_Golem;
class GAME_Titan;

struct ARENA_Tile {

    baseplate::Vector2 SourcePosition;

    bool Obstacle;

    ARENA_Tile(baseplate::Vector2 source_position, bool obstacle) : SourcePosition(source_position), Obstacle(obstacle) {}
};

class GAME_Arena : public baseplate::Node2D, private baseplate::AssetData {
private:

    GAME_DisplayManager* mDisplayManager = nullptr;

    unsigned int mCurrentRound = 1;

    bool Builded = false;

    baseplate::Vector2 m_TileSize = 0;
    baseplate::Vector2 m_TileSourceSize = 0;
    baseplate::Vector2 m_TileOffset = 0;

    std::unordered_map<int, ARENA_Tile*> m_Tileset;
    std::vector<std::pair<baseplate::Vector2i, int>> m_Tilemap;

    std::string m_JsonPath = "";

    GAME_Golem* m_CurrentGolem = nullptr;

public:

    GAME_Arena(const char* json_path) : m_JsonPath(json_path), baseplate::Node2D("arena", 0, 0) {}

private:

    bool TestTileClicked(baseplate::Vector2 click_position, baseplate::Vector2i tile_position);

    void SelectGolem(GAME_Golem* golem);
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
    void _Draw() override;
    void _Process(double delta) override;
};