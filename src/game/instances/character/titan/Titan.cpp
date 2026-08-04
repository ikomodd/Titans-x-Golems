#include "Titan.hpp"

#include <iostream>

#include "../golem/Golem.hpp"
#include "game/instances/arena/Arena.hpp"

//

game::titan::TargetData game::Titan::GetTargetData() {

    auto* arena = GetParent<Arena>();

    for (Vector2i attack_direction : m_attackDirections)  {

        Vector2i currentTarget = m_tilePosition + attack_direction;

        if (!arena->IsAValidTile(currentTarget, true))
            continue;
        
        for (iNode* arena_child : arena->GetChildren()) {

            auto* golem = arena_child->As<Golem>();
            if (golem && golem->GetTilePosition() == currentTarget)
                return titan::TargetData(true, currentTarget);
        }
    }
    return titan::TargetData(false, 0);
}

baseplate::Vector2i game::Titan::GetNextStep() {

    auto* arena = GetParent<Arena>();

    std::vector<Vector2i> smallPath;
    size_t stepCount = INT_MAX;

    for (iNode* arena_child : arena->GetChildren()) {

        auto* golem = arena_child->As<Golem>();
        if (golem) {

            for (Vector2i attack_direction : m_attackDirections)  {

                Vector2i currentTarget = golem->GetTilePosition() - attack_direction;

                if (!arena->IsAValidTile(currentTarget))
                    continue;

                std::vector<Vector2i> currentBFS = arena->MakeBFS(this, m_tilePosition, currentTarget);
                
                if (currentBFS.size() < stepCount) {

                    stepCount = currentBFS.size();
                    smallPath = currentBFS;
                }
            }
        }
    }

    return smallPath.front();
}

void game::Titan::RunIa() {

    auto* arena = GetParent<Arena>();

    while (m_actions > 0) {

        titan::TargetData targetData = GetTargetData();

        if (targetData.inTarget)
            AttackOn(targetData.tile);
        else
            MoveTo(GetNextStep());
    }
}