#pragma once

#include "../Character.hpp"

namespace game::titan {

    struct TileData {

        bool inTarget;
            
        baseplate::Vector2i tile;
        baseplate::Vector2i direction;

        TileData(bool in_target, baseplate::Vector2i tile, baseplate::Vector2i direction) : inTarget(in_target), tile(tile), direction(direction) {}
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