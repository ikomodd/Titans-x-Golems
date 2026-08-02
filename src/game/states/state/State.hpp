#pragma once

#include "baseplate/instances/node/Node.hpp"

namespace game {

    class GameState : public baseplate::Node {
    private:

    public:

        void Initialize() override;

        GameState(const char* name) : baseplate::Node(name) {}
    };
}