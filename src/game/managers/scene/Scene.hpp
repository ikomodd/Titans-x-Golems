#pragma once

#include "baseplate/manager/Manager.hpp"

#include <stack>

namespace game {

    class Origin;

    class SceneManager : public baseplate::Manager<SceneManager> {
    private:

        SceneManager() : baseplate::Manager<SceneManager>("scene_manager") {};
        friend class baseplate::Manager<SceneManager>;

        std::stack<Origin*> m_sceneStack;

    public:

        void PlayScene(Origin* origin);
        void CloseCurrentScene();

        //

        template <typename T = Origin>
        T* GetCurrentScene() {

            return dynamic_cast<T*>(m_sceneStack.top());
        }

        //

        void Process() override;
    };
}