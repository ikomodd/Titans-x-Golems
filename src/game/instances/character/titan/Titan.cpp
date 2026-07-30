#include "Titan.hpp"

#include <iostream>
#include "baseplate/utils/random/Random.hpp"

#include "../golem/Golem.hpp"

// [TODO] Todo esse sistema ta errado

game::titan::TileData game::Titan::GetTileData() {


    return titan::TileData(false, 0, 0);
}

//

void game::Titan::RunIa() {

    while (mActions > 0) {

        titan::TileData TileData = GetTileData();

        if (TileData.InTarget) {

            std::cout << "atacando em: " << TileData.Tile.ToString() << "\n";
            AttackOn(TileData.Tile);
        }
        else {

            MoveTo(mTilePosition + TileData.Direction);
        }
    }
}