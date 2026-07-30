#pragma once

#include "../Character.hpp"

class GAME_Golem;

struct TITAN_TileData {

    bool InTarget;
    
    baseplate::Vector2i Tile;
    baseplate::Vector2i Direction;

    TITAN_TileData(bool in_target, baseplate::Vector2i tile, baseplate::Vector2i direction) : InTarget(in_target), Tile(tile), Direction(direction) {}
};

class GAME_Titan : public GAME_Character {
public:

    GAME_Titan(baseplate::Vector2i tile_position, std::string source_path) : GAME_Character(tile_position, source_path) {}

private:

    TITAN_TileData GetTileData();

public:

    void RunIa();
};