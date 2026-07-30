#pragma once

#include <iostream>
#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

class GAME_StateManager;

class GAME_CoreManager : public baseplate::Manager<GAME_CoreManager> {
private:

    GAME_StateManager* m_StateManager = nullptr;

    GAME_CoreManager() : baseplate::Manager<GAME_CoreManager>("core_manager") {}
    friend class baseplate::Manager<GAME_CoreManager>;

public:

    bool Running = true;

    void _Init() override;
    void _Event(SDL_Event& event) override;
    void _Process() override;
    void _Close() override;
};