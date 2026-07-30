#include "Core.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void game::CoreManager::_Init() {

    mStateManager = &baseplate::Manager<StateManager>::Get();
}

void game::CoreManager::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_QUIT)
        Running = false;

    auto LinearStateChildren = mStateManager->GetCurrentState()->GetLinearChildren();
    for (baseplate::iNode* inode : LinearStateChildren) {

        inode->_Event(event);
    }
}

void game::CoreManager::_Process() {

    auto LinearStateChildren = mStateManager->GetCurrentState()->GetLinearChildren();
    for (size_t i = 0; i < LinearStateChildren.size(); ) {

        baseplate::iNode* iNode = LinearStateChildren[i];
        iNode->_Process(0.0);

        if (iNode->DestroyMark) {

            auto* MarkedNode = static_cast<baseplate::Node*>(iNode);

            for (auto* node_child : MarkedNode->GetChildren()) {
                node_child->Destroy();
            }

            MarkedNode->GetParent()->As<baseplate::Node>()->RemoveNode(iNode);
            LinearStateChildren.erase(LinearStateChildren.begin() + i);

            std::cout << "[game::CoreManager] Node: " << iNode->Name << " deletado com sucesso\n";

            delete iNode;
        }
        else i++;
    }
}

void game::CoreManager::_Close() {
    
}