#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <string>

namespace baseplate {

    class Children;

    class iNode {
    private:

        bool m_initialized = false;

        iNode* m_parent = nullptr;
        
    public:

        bool destroyMark = false;

        std::string name;

        iNode(std::string name) : name(name) {}
        friend class Children;
        virtual ~iNode() = default;

        bool IsInitialized() {

            return m_initialized;
        }

        // Chama o Ready e marca o iNode como inicializado

        virtual void Initialize() {

            m_initialized = true;
            Ready();
        }

        // Marca o iNode para ser destruido no core [OBS] possivel erro se o node for destruido e depois algum node precisar dele

        void Destroy() {

            destroyMark = true;
        }

        // Retorna o mParent, o parent foi colocado aqui ao invés de ficar no baseplate::children por motivos maiores

        template <typename T = iNode>
        T* GetParent() {

            return dynamic_cast<T*>(m_parent);
        }

        // Cast seguro para outro tipo

        template<typename T>
        T* As() {

            return dynamic_cast<T*>(this);
        }

        //

        virtual void Ready() = 0;
        virtual void Event(const SDL_Event& event) = 0;
        virtual void Draw(GLuint vao, glm::mat4 projection) = 0;
        virtual void Process(double delta) = 0;
        virtual void Close() = 0;
    };
}