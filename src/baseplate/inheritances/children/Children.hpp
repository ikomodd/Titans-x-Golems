#pragma once

#include <vector>

#include "../../instances/node/iNode.hpp"

class BSPLT_Node;

class BSPLT_Children {
private:

    BSPLT_iNode* m_Parent = nullptr;
    std::vector<BSPLT_iNode*> m_Children = {};

public:

    void AddNode(BSPLT_Node* inode);
    void RemoveNode(BSPLT_Node* inode);

    bool HasNode(const char* name);

    std::vector<BSPLT_Node*> GetLinearChildren();
    std::vector<BSPLT_Node*> GetChildren();

    //

    template <typename T = BSPLT_Node>
    T* GetNode(const char* name) {

        for (size_t i = 0; i <= m_Children.size(); i++) {
            BSPLT_iNode* iNode = m_Children[i];

            if (iNode->Name == name)
                return dynamic_cast<T*>(iNode);
        }
        return nullptr;
    }

    template <typename T = BSPLT_Node>
    T* GetParent() {

        return dynamic_cast<T*>(m_Parent);
    }
};