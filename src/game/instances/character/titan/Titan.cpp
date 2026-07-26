#include "Titan.hpp"

#include <iostream>
#include "baseplate/utils/random/Random.hpp"

#include "../golem/Golem.hpp"

TITAN_TileData GAME_Titan::GetTileData() {

    int MinLengthOfTileToGolemSquared = INT_MAX;
    GAME_Golem* NearestGolemOfTile = nullptr;
    Vector2i NearestTileToGolem;

    for (Vector2i tile : m_AttackDirections) {

        Vector2i TileInWorld = m_TilePosition + tile;

        int MinLengthSquared = INT_MAX;
        GAME_Golem* NearestGolem = nullptr;

        for (auto* node : GetParent()->GetChildren()) {

            GAME_Golem* Golem = node->As<GAME_Golem>();
            if (Golem) {

                int LengthSquared = (Golem->GetTilePosition() - TileInWorld).LengthSquared();
                if (LengthSquared < MinLengthSquared) {

                    MinLengthSquared = LengthSquared;
                    NearestGolem = Golem;
                }
            }
        }

        if (MinLengthSquared < MinLengthOfTileToGolemSquared) {

            MinLengthOfTileToGolemSquared = MinLengthSquared;
            NearestGolemOfTile = NearestGolem;
            NearestTileToGolem = TileInWorld;
        }
    }

    bool InTarget = (MinLengthOfTileToGolemSquared == 0);
    Vector2i Direction = (NearestGolemOfTile->GetTilePosition().ToVector2() - NearestTileToGolem.ToVector2()).Normalize().Sign().ToVector2i();

    std::cout << InTarget << " " << NearestTileToGolem.ToString() << " " << Direction.ToString() << "\n";

    return TITAN_TileData(InTarget, NearestTileToGolem, Direction);
}

//

void GAME_Titan::RunIa() {

    while (m_Actions > 0) {

        TITAN_TileData TileData = GetTileData();

        if (TileData.InTarget) {

            std::cout << "atacando em: " << TileData.Tile.ToString() << "\n";
            AttackOn(TileData.Tile);
        }
        else {

            MoveTo(m_TilePosition + TileData.Direction);
        }
    }
}