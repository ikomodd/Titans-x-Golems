#include "Scene.hpp"

#include "game/origins/Origin.hpp"

// Controle

void game::SceneManager::PlayScene(Origin* origin) {

    m_sceneStack.push(origin);

    origin->Initialize();
}

void game::SceneManager::CloseCurrentScene() {

    m_sceneStack.pop();
}

//

void game::SceneManager::Process() {

    // Deleta nodes marcados

    auto linearSceneChildren = GetCurrentScene()->GetLinearChildren();

    for (size_t i = 0; i < linearSceneChildren.size(); ) {

        baseplate::iNode* inode = linearSceneChildren[i];

        if (inode->destroyMark) {

            auto* MarkedNode = static_cast<baseplate::Node*>(inode);

            for (auto* node_child : MarkedNode->GetChildren()) {
                node_child->Destroy();
            }

            MarkedNode->GetParent()->As<baseplate::Node>()->RemoveNode(inode);
            linearSceneChildren.erase(linearSceneChildren.begin() + i);

            std::cout << "[game::CoreManager] Node: " << inode->name << " deletado com sucesso\n";

            delete inode;
        }
        else i++;
    }
}