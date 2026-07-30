#pragma once

#include "baseplate/manager/Manager.hpp"
#include "baseplate/data_models/stack/Stack.hpp"

class GAME_GameState;

class GAME_StateManager : public baseplate::Manager<GAME_StateManager> {
private:

    GAME_StateManager() : baseplate::Manager<GAME_StateManager>("state_manager") {};
    friend class baseplate::Manager<GAME_StateManager>;

    baseplate::Stack<GAME_GameState*> StateStack;

public:

    void PlayState(GAME_GameState* state);
    void CloseCurrentState();

    //

    template <typename T = GAME_GameState>
    GAME_GameState* GetCurrentState() {

        return dynamic_cast<T*>(StateStack.Get());
    }

    //

    void _Init() override;
    void _Event(SDL_Event& event) override;
    void _Process() override;
    void _Close() override;
};