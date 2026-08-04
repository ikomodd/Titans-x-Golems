#pragma once

#include "../Character.hpp"

namespace game::titan {

    struct TargetData {

        bool inTarget;
        baseplate::Vector2i tile;

        TargetData(bool in_target, baseplate::Vector2i tile) : inTarget(in_target), tile(tile) {}
    };
}

namespace game {

    class Golem;

    class Titan : public Character {
    private:

        using Vector2 = baseplate::Vector2;
        using Vector2i = baseplate::Vector2i;

         titan::TargetData GetTargetData();
        Vector2i GetNextStep();

    public:

        Titan(baseplate::Vector2i tile_position, std::string source_path) : Character(tile_position, source_path) {}

        void RunIa();
    };
}