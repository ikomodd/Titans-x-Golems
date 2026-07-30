#pragma once

#include "baseplate/instances/node/Node.hpp"

class GAME_GameState : public baseplate::Node {
private:

public:

    void _Initialize() override;

    GAME_GameState(const char* name) : baseplate::Node(name) {}
};