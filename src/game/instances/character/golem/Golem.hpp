#pragma once

#include "../Character.hpp"

namespace game {

    class Golem : public Character {
    public:

        Golem(baseplate::Vector2i tile_position, std::string source_path) : Character(tile_position, source_path) {}

        void TileSelected(baseplate::Vector2i tile) {

            MoveTo(tile);
        }
    };
}