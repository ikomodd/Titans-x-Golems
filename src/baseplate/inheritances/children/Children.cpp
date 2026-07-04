#include "Children.hpp"

#include <iostream>

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

#include "../../instances/node/Node.hpp"

void BSPLT_Children::AddNode(BSPLT_Node* node) {

    auto* Node = static_cast<BSPLT_Node*>(node);
    auto* ThisNode = static_cast<BSPLT_Node*>(this);

    //

    if (Node->m_Parent) {
        std::cerr << "[BASEPLATE_CHILDREN] Não foi possivel adicionar o node: " << Node->Name << " em: " << ThisNode->Name << ". O node ja tem um pai\n";
        return;
    }

    //

    m_Children.push_back(node);
    Node->m_Parent = ThisNode;

    //

    GAME_StateManager& StateManager = BSPLT_Manager<GAME_StateManager>::Get();
    GAME_GameState* CurrentState = StateManager.GetCurrentState();

    if (CurrentState->IsInitialized())
        Node->_Ready();
}

void BSPLT_Children::RemoveNode(BSPLT_Node* node) {


}

bool BSPLT_Children::HasNode(const char* name) {

    for (size_t i = 0; i <= m_Children.size(); i++) {
        BSPLT_iNode* iNode = m_Children[i];

        if (iNode->Name == name)
            return true;
    }
    return false;
}

std::vector<BSPLT_Node*> BSPLT_Children::GetLinearChildren() {

    std::vector<BSPLT_Node*> Result;

    for (BSPLT_iNode* inode : m_Children) {

        BSPLT_Node* Node = static_cast<BSPLT_Node*>(inode);

        Result.push_back(Node);

        auto NodeLinearChildren = Node->GetLinearChildren();
        Result.insert(Result.end(), NodeLinearChildren.begin(), NodeLinearChildren.end());


    }

    return Result;
}

std::vector<BSPLT_Node*> BSPLT_Children::GetChildren() {

    std::vector<BSPLT_Node*> Result = {};

    for (BSPLT_iNode* inode : m_Children) {

        Result.push_back(static_cast<BSPLT_Node*>(inode));
    }

    return Result;
}