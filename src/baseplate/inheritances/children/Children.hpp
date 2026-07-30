#pragma once

#include <vector>

#include "../../instances/node/iNode.hpp"

namespace baseplate {

    class Node;

    class Children {
    private:

        iNode* mOwner = nullptr; // [NOTE] Depois tira isso e da cast direto pra iNode

        std::vector<iNode*> mChildren = {};

    public:

    Children(iNode* owner_node) : mOwner(owner_node) {}

        // Adiciona um iNode na lista

        void AddNode(iNode* inode) {

            // Verifica se o iNode já pertence a algum Children

            if (inode->mParent) {
                std::cerr << "[baseplate::Children] Não foi possivel adicionar o node: " << inode->Name << " em: " << mOwner->Name << ". O node ja tem um pai\n";
                return;
            }

            // Adiciona inode na lista e define seu pai como mOwner

            mChildren.push_back(inode);
            inode->mParent = mOwner;

            // [OBS] Elemento de Game em Baseplate, não pode

            /*
                Possivel solução: Colocar "bool mInitialized no inode e pegar o state diretamente pela tree,
                já que GAME_State também é um node"
            */

            iNode* Origin = GetOrigin();

            if (Origin->IsInitialized()) {

                inode->_Initialize();
            }
        }

        // Remove um iNode da lista

        void RemoveNode(iNode* inode) {

            for (size_t i = 0; i < mChildren.size(); i++) {

                iNode* Current = mChildren[i];
                if (Current == inode) {
                    
                    mChildren.erase(mChildren.begin() + i);
                    break;
                }
            }
        }

        // Verifica se um iNode pertence a lista

        bool HasNode(std::string node_name) {

            for (auto* child : mChildren) {

                if (child->Name == node_name)
                    return true;
            }
            return false;
        }

        // Agrupa todos os iNodes e seus filhos em um só vector

        std::vector<iNode*> GetLinearChildren() {

            std::vector<iNode*> Result;

            for (iNode* child : mChildren) {

                Result.push_back(child);

                auto* ChildChildren = dynamic_cast<Children*>(child);
                Result.insert(Result.end(), ChildChildren->mChildren.begin(), ChildChildren->mChildren.end());
            }

            return Result;
        }

        // Retorna uma copia da mChildren

        std::vector<iNode*> GetChildren() {

            return mChildren;
        }

        iNode* GetOrigin() {

            if (mOwner->mParent)
                return dynamic_cast<Children*>(mOwner->mParent)->GetOrigin();
            else
                return dynamic_cast<iNode*>(mOwner);
        }

        // Retorna um iNode da lista

        template <typename T = iNode>
        T* GetNode(std::string name) {

            for (size_t i = 0; i <= mChildren.size(); i++) {
                iNode* Child = mChildren[i];

                if (Child->Name == name)
                    return dynamic_cast<T*>(Child);
            }
            return nullptr;
        }

    };
}