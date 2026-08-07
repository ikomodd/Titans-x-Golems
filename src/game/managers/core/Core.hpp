#pragma once

#include <iostream>
#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

namespace game {

    class SceneManager;

    class CoreManager : public baseplate::Manager<CoreManager> {
    private:

        SceneManager* m_sceneManager = nullptr;

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