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

//

void game::StateManager::Process() {

    // Deleta nodes marcados

    /*
        [OBS]
    */

    auto linearStateChildren = GetCurrentState()->GetLinearChildren();

    for (size_t i = 0; i < linearStateChildren.size(); ) {

        baseplate::iNode* inode = linearStateChildren[i];

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