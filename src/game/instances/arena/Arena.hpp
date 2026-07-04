#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "baseplate/instances/node2d/Node2D.hpp"
#include "game/inheritances/asset_data/AssetData.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"
#include "baseplate/data_models/vector/Vector2Int.hpp"

class GAME_Character;

struct ARENA_Tile {

    Vector2 SourcePosition;
    Vector2 SourceSize;

    bool Collidible;

    ARENA_Tile(Vector2 source_position, Vector2 source_size, bool collidible) : SourcePosition(source_position), SourceSize(source_size), Collidible(collidible) {}
};

class GAME_Arena : public BSPLT_Node2D, private GAME_AssetData {
private:

    Vector2 m_TileSize = 0;
    Vector2 m_TileOffset = 0;

    std::unordered_map<int, ARENA_Tile*> m_Tileset;
    std::vector<std::pair<Vector2i, int>> m_Tilemap;

    std::string m_JsonPath = "";

    GAME_Character* m_CharacterSelected = nullptr;

public:

    GAME_Arena(const char* json_path) : m_JsonPath(json_path), BSPLT_Node2D("arena", 0, 0) {}

private:

    bool TestTileClicked(Vector2 click_position, Vector2i tile_position);
    void BuildArena();

public:

    Vector2 GetTileSize() {
        return m_TileSize;
    }

    void _Ready() override;
    void _Event(SDL_Event& event) override;
    void _Draw(SDL_Renderer* renderer) override;
    void _Process(double delta) override;
};