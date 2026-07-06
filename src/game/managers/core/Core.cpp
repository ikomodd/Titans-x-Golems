#include "Core.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

void GAME_CoreManager::_Init() {


}

void GAME_CoreManager::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_QUIT)
        Running = false;

    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();

    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();
    for (BSPLT_Node* node : LinearStateChildren) {

        node->_Event(event);
    }
}

void GAME_CoreManager::_Process() {
    
    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();

    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();
    for (size_t i = 0; i < LinearStateChildren.size(); ) {

        BSPLT_Node* Node = LinearStateChildren[i];
        Node->_Process(0.0);

        if (Node->m_DestroyMark) {

            for (auto* node_child : Node->GetChildren()) {
                node_child->Destroy();
            }

            Node->GetParent()->RemoveNode(Node);
            LinearStateChildren.erase(LinearStateChildren.begin() + i);

            std::cout << "[GAME_Core] Node: " << Node->Name << " deletado com sucesso\n";

            delete Node;
        }
        else i++;
    }
}

void GAME_CoreManager::_Close() {
    
}