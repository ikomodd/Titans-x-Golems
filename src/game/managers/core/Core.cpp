#include "Core.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void game::CoreManager::Init() {

    m_stateManager = &baseplate::Manager<StateManager>::Get();
}

void game::CoreManager::Event(const SDL_Event& event) {

    if (event.type == SDL_EVENT_QUIT)
        running = false;

    auto linearStateChildren = m_stateManager->GetCurrentState()->GetLinearChildren();
    for (baseplate::iNode* inode : linearStateChildren) {

        inode->Event(event);
    }
}

void game::CoreManager::Process() {

    auto linearStateChildren = m_stateManager->GetCurrentState()->GetLinearChildren();
    for (size_t i = 0; i < linearStateChildren.size(); ) {

        baseplate::iNode* inode = linearStateChildren[i];
        inode->Process(0.0);

        if (inode->destroyMark) {

            auto* MarkedNode = static_cast<baseplate::Node*>(inode);

            for (auto* node_child : MarkedNode->GetChildren()) {
                node_child->Destroy();
            }

            MarkedNode->GetParent()->As<baseplate::Node>()->RemoveNode(inode);
            linearStateChildren.erase(linearStateChildren.begin() + i);

            std::cout << "[game::CoreManager] Node: " << inode->name << " deletado com sucesso\n";

            delete inode;
        }
        else i++;
    }
}

void game::CoreManager::Close() {
    
}