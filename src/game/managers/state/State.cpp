#include "State.hpp"

#include "game/states/state/State.hpp"

// Controle

void game::StateManager::PlayState(GAME_GameState* state) {

    mStateStack.Push(state);

    state->_Initialize();
}

void game::StateManager::CloseCurrentState() {

    mStateStack.Pop();
}