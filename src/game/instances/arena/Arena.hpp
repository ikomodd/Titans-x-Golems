#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "baseplate/instances/node2d/Node2D.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"
#include "baseplate/data_models/vector/Vector2Int.hpp"

class GAME_Character;
class GAME_Golem;
class GAME_Titan;

struct ARENA_Tile {

    Vector2 SourcePosition;

    bool Obstacle;

    ARENA_Tile(Vector2 source_position, bool obstacle) : SourcePosition(source_position), Obstacle(obstacle) {}
};

class GAME_Arena : public BSPLT_Node2D, private BSPLT_AssetData {
private:

    unsigned int m_CurrentRound = 1;

    bool Builded = false;

    Vector2 m_TileSize = 0;
    Vector2 m_TileSourceSize = 0;
    Vector2 m_TileOffset = 0;

    std::unordered_map<int, ARENA_Tile*> m_Tileset;
    std::vector<std::pair<Vector2i, int>> m_Tilemap;

    std::string m_JsonPath = "";

    GAME_Golem* m_CurrentGolem = nullptr;

public:

    GAME_Arena(const char* json_path) : m_JsonPath(json_path), BSPLT_Node2D("arena", 0, 0) {}

private:

    bool TestTileClicked(Vector2 click_position, Vector2i tile_position);

    void SelectGolem(GAME_Golem* golem);
    void UnselectGolem();

    void BuildArena();

    void PlayerRoundEnded();

public:

    Vector2 GetTileSize() {
        return m_TileSize;
    }



    bool CanMoveTo(Vector2i tile);

    void AttackTile(Vector2i tile, float damage);

    void _Ready() override;
    void _Event(SDL_Event& event) override;
    void _Draw() override;
    void _Process(double delta) override;
};