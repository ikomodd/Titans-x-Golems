#pragma once

#include "baseplate/manager/Manager.hpp"
#include "baseplate/data_models/stack/Stack.hpp"

class GAME_GameState;

namespace game {

    class StateManager : public baseplate::Manager<StateManager> {
    private:

        StateManager() : baseplate::Manager<StateManager>("state_manager") {};
        friend class baseplate::Manager<StateManager>;

        baseplate::Stack<GAME_GameState*> mStateStack;

    public:

        void PlayState(GAME_GameState* state);
        void CloseCurrentState();

        //

        template <typename T = GAME_GameState>
        GAME_GameState* GetCurrentState() {

            return dynamic_cast<T*>(mStateStack.Get());
        }
    };
}