#include "State.hpp"

#include "game/states/state/State.hpp"

// Controle

void game::StateManager::PlayState(GameState* state) {

    m_stateStack.Push(state);

    state->Initialize();
}

void game::StateManager::CloseCurrentState() {

    m_stateStack.Pop();
}