#include "Interface.hpp"

#include "game/origins/Origin.hpp"

void game::InterfaceManager::PlayInterface(Origin* origin) {

    m_interfaceStack.push(origin);
    origin->Initialize();
}

void game::InterfaceManager::CloseCurrentInterface() {

    m_interfaceStack.pop();
}

void game::InterfaceManager::Process() {

    auto linearInterfaceChildren = m_interfaceStack.top()->GetLinearChildren();

    for (size_t i = 0; i < linearInterfaceChildren.size(); ) {

        baseplate::iNode* inode = linearInterfaceChildren[i];

        if (inode->destroyMark) {

            auto* MarkedNode = static_cast<Node*>(inode);

            for (auto* node_child : MarkedNode->GetChildren()) {
                node_child->Destroy();
            }

            MarkedNode->GetParent()->As<Node>()->RemoveNode(inode);
            linearInterfaceChildren.erase(linearInterfaceChildren.begin() + i);

            std::cout << "[game::InterfaceManager] Node: " << inode->name << " deletado com sucesso\n";

            delete inode;
        }
        else i++;
    }
}