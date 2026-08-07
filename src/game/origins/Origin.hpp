#pragma once

#include "game/instances/node/Node.hpp"
#include "baseplate/inheritances/children/Children.hpp"

namespace game {

    class Origin : public Node {
    public:

        Origin(std::string name) : Node(name) {}

        void Initialize() override;
    };
}