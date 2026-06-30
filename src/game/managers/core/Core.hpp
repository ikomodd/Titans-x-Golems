#pragma once

#include <iostream>
#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

class GAME_CoreManager : public BSPLT_Manager<GAME_CoreManager> {
private:

    GAME_CoreManager() : BSPLT_Manager("core_manager") {}
    friend class BSPLT_Manager<GAME_CoreManager>;

public:

    bool Running = true;

    void _Init() override;
    void _Event(SDL_Event& event) override;
    void _Process() override;
    void _Close() override;
};