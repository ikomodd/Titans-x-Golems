#include "Core.hpp"

#include "game/managers/scene/Scene.hpp"
#include "game/origins/Origin.hpp"

void game::CoreManager::Init() {

    m_sceneManager = &baseplate::Manager<SceneManager>::Get();
}

void game::CoreManager::Event(const SDL_Event& event) {

    // Fecha o loop ao dar quit

    if (event.type == SDL_EVENT_QUIT)
        running = false;

    // Passa o event para os nodes da cena atual

    auto linearSceneChildren = m_sceneManager->GetCurrentScene()->GetLinearChildren();
    for (baseplate::iNode* inode : linearSceneChildren) {

        inode->Event(event);
    }
}

void game::CoreManager::Process() {

    // Lista linear de todos os nodes da cena atual

    auto linearSceneChildren = m_sceneManager->GetCurrentScene()->GetLinearChildren();

    // Chama o virtual Process() nos inodes da lista

    for (baseplate::iNode* inode : linearSceneChildren) {

        inode->Process(0.0);
    }
}

void game::CoreManager::Close() {
    
}