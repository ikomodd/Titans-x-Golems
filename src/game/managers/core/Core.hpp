#pragma once

#include <iostream>
#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

namespace game {

    class StateManager;

    class CoreManager : public baseplate::Manager<CoreManager> {
    private:

        StateManager* m_stateManager = nullptr;

        CoreManager() : baseplate::Manager<CoreManager>("core_manager") {}
        friend class baseplate::Manager<CoreManager>;

    public:

        bool running = true;

        void Init() override;
        void Event(const SDL_Event& event) override;
        void Process() override;
        void Close() override;
    };
}