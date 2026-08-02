#pragma once

#include "../state/State.hpp"

namespace game::txg {

    class MainState : public GameState {
    public:

        MainState() : GameState("main_state") {}

        void Ready() override;
    };
}