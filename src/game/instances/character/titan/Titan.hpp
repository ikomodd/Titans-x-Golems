#pragma once

#include "../Character.hpp"

namespace game::titan {

    struct TileData {

        bool InTarget;
            
        baseplate::Vector2i Tile;
        baseplate::Vector2i Direction;

        TileData(bool in_target, baseplate::Vector2i tile, baseplate::Vector2i direction) : InTarget(in_target), Tile(tile), Direction(direction) {}
    };
}

namespace game {

    class Golem;

    class Titan : public Character {
    public:

        Titan(baseplate::Vector2i tile_position, std::string source_path) : Character(tile_position, source_path) {}

    private:

        titan::TileData GetTileData();

    public:

        void RunIa();
    };
}