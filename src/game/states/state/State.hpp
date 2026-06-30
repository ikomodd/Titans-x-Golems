#pragma once

#include "baseplate/instances/node/Node.hpp"

class GAME_GameState : public BSPLT_Node {
private:

    bool m_Initialized = false;

public:

    bool IsInitialized() { return m_Initialized; }

    void Initialize();

    GAME_GameState(const char* name) : BSPLT_Node(name) {}
};