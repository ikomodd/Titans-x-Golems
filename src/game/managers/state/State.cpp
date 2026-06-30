#include "State.hpp"

#include "game/states/state/State.hpp"

// Controle

void GAME_StateManager::PlayState(GAME_GameState* state) {

    StateStack.Push(state);
    state->Initialize();
}

void GAME_StateManager::CloseCurrentState() {

    StateStack.Pop();
}

// Herança

void GAME_StateManager::_Init() {

}

void GAME_StateManager::_Event(SDL_Event& event) {


}

void GAME_StateManager::_Process() {


}

void GAME_StateManager::_Close() {


}