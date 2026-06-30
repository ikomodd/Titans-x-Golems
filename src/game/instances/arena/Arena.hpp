#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "baseplate/instances/node/Node.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"
#include "baseplate/data_models/vector/Vector2Int.hpp"

struct ARENA_Tile {

    Vector2i SourcePosition;
    Vector2i SourceSize;

    bool Collidible;

    ARENA_Tile(Vector2i source_position, Vector2i source_size, bool collidible) : SourcePosition(source_position), SourceSize(source_size), Collidible(collidible) {}
};

class GAME_Arena : public BSPLT_Node {
private:

    Vector2 m_TileSize = 0;

    Vector2 m_OffsetPosition = 0;

    std::unordered_map<int, ARENA_Tile*> m_Tileset;
    std::vector<std::vector<int>> m_Tilemap;

    std::string m_JsonPath;

public:

    GAME_Arena(const char* json_path) : m_JsonPath(json_path), BSPLT_Node("arena") {}

private:

    void BuildArena();

public:

    void _Ready() override;
    void _Draw(SDL_Renderer* renderer) override;
};