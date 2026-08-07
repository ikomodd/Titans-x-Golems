#pragma once

#include "baseplate/instances/node/Node.hpp"
#include "baseplate/inheritances/children/Children.hpp"

namespace game {

    class Origin : public baseplate::Node {
    public:

        Origin(std::string name) : baseplate::Node(name) {}

        void Initialize() override;
    };
}