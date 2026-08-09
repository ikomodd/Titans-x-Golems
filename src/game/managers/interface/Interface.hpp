#pragma once

#include "baseplate/manager/Manager.hpp"

#include <stack>

namespace game {

    class Origin;

    class InterfaceManager : public baseplate::Manager<InterfaceManager> {
    private:
        
        InterfaceManager() : baseplate::Manager<InterfaceManager>("interface_manager") {}
        friend class baseplate::Manager<InterfaceManager>;

        std::stack<Origin*> m_interfaceStack;

    public:

        void PlayInterface(Origin* origin);
        void CloseCurrentInterface();

        //

        template <typename T = Origin>
        T* GetCurrentInterface() {

            return dynamic_cast<T*>(m_interfaceStack.top());
        }

        //

        void Process() override;
    };
}