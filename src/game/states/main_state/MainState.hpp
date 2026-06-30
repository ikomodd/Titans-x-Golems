#pragma once

#include "../state/State.hpp"

class GAME_MainState : public GAME_GameState {
public:

    GAME_MainState() : GAME_GameState("main_state") {}

    void _Ready() override;
};