#pragma once

#include <vector>

#include "../../instances/node/iNode.hpp"

namespace baseplate {

    class Node;

    class Children {
    private:

        iNode* m_owner = nullptr; // [NOTE] Depois tira isso e da cast direto pra iNode

        std::vector<iNode*> m_children = {};

    public:

    Children(iNode* owner_node) : m_owner(owner_node) {}

        // Adiciona um iNode na lista

        void AddNode(iNode* inode) {

            // Verifica se o iNode já pertence a algum Children

            if (inode->m_parent) {
                std::cerr << "[baseplate::Children] Não foi possivel adicionar o node: " << inode->name << " em: " << m_owner->name << ". O node ja tem um pai\n";
                return;
            }

            // Adiciona inode na lista e define seu pai como mOwner

            m_children.push_back(inode);
            inode->m_parent = m_owner;

            // Pega o origin da tree e verifica se está iniciado, se tiver, inicia o node aqui mesmo

            iNode* Origin = GetOrigin();

            if (Origin->IsInitialized()) {

                inode->Initialize();
            }
        }

        // Remove um iNode da lista

        void RemoveNode(iNode* inode) {

            for (size_t i = 0; i < m_children.size(); i++) {

                iNode* current = m_children[i];
                if (current == inode) {
                    
                    m_children.erase(m_children.begin() + i);
                    break;
                }
            }
        }

        // Verifica se um iNode pertence a lista

        bool HasNode(std::string node_name) {

            for (auto* child : m_children) {

                if (child->name == node_name)
                    return true;
            }
            return false;
        }

        // Agrupa todos os iNodes e seus filhos em um só vector

        std::vector<iNode*> GetLinearChildren() {

            std::vector<iNode*> Result;

            for (iNode* child : m_children) {

                Result.push_back(child);

                auto* childChildren = dynamic_cast<Children*>(child);
                Result.insert(Result.end(), childChildren->m_children.begin(), childChildren->m_children.end());
            }

            return Result;
        }

        // Retorna uma copia da mChildren

        std::vector<iNode*> GetChildren() {

            return m_children;
        }

        iNode* GetOrigin() {

            if (m_owner->m_parent)
                return dynamic_cast<Children*>(m_owner->m_parent)->GetOrigin();
            else
                return dynamic_cast<iNode*>(m_owner);
        }

        // Retorna um iNode da lista

        template <typename T = iNode>
        T* GetNode(std::string name) {

            for (size_t i = 0; i <= m_children.size(); i++) {
                iNode* child = m_children[i];

                if (child->name == name)
                    return dynamic_cast<T*>(child);
            }
            return nullptr;
        }

    };
}