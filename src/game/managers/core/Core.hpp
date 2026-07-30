#pragma once

#include <iostream>
#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

namespace game {

    class StateManager;

    class CoreManager : public baseplate::Manager<CoreManager> {
    private:

        StateManager* mStateManager = nullptr;

        CoreManager() : baseplate::Manager<CoreManager>("core_manager") {}
        friend class baseplate::Manager<CoreManager>;

    public:

        bool Running = true;

        void _Init() override;
        void _Event(SDL_Event& event) override;
        void _Process() override;
        void _Close() override;
    };
}