#pragma once

#include "../Character.hpp"

class GAME_Golem : public GAME_Character {
public:

    GAME_Golem(Vector2i tile_position, std::string source_path) : GAME_Character(tile_position, source_path) {}

    void TileSelected(Vector2i tile) {

        MoveTo(tile);
    }
};