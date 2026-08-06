#include "Core.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void game::CoreManager::Init() {

    m_stateManager = &baseplate::Manager<StateManager>::Get();
}

void game::CoreManager::Event(const SDL_Event& event) {

    // Fecha o loop ao dar quit

    if (event.type == SDL_EVENT_QUIT)
        running = false;

    // Passa o event para os nodes do state atual

    auto linearStateChildren = m_stateManager->GetCurrentState()->GetLinearChildren();
    for (baseplate::iNode* inode : linearStateChildren) {

        inode->Event(event);
    }
}

void game::CoreManager::Process() {

    // Lista linear de todos os nodes do state atual

    auto linearStateChildren = m_stateManager->GetCurrentState()->GetLinearChildren();

    // Chama o virtual Process() nos inodes da lista

    for (baseplate::iNode* inode : linearStateChildren) {

        inode->Process(0.0);
    }
}

void game::CoreManager::Close() {
    
}