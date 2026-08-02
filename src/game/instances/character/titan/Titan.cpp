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

    while (m_actions > 0) {

        titan::TileData tileData = GetTileData();

        if (tileData.inTarget) {

            std::cout << "atacando em: " << tileData.tile.ToString() << "\n";
            AttackOn(tileData.tile);
        }
        else {

            MoveTo(m_tilePosition + tileData.direction);
        }
    }
}