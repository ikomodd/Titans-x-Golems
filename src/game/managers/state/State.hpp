#pragma once

#include "baseplate/manager/Manager.hpp"
#include "baseplate/data_models/stack/Stack.hpp"



namespace game {

    class GameState;

    class StateManager : public baseplate::Manager<StateManager> {
    private:

        StateManager() : baseplate::Manager<StateManager>("state_manager") {};
        friend class baseplate::Manager<StateManager>;

        baseplate::Stack<GameState*> m_stateStack;

    public:

        void PlayState(GameState* state);
        void CloseCurrentState();

        //

        template <typename T = GameState>
        GameState* GetCurrentState() {

            return dynamic_cast<T*>(m_stateStack.Get());
        }
    };
}