#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <string>

namespace baseplate {

    class Children;

    class iNode {
    private:

        bool mInitialized = false;

        iNode* mParent = nullptr;
        
    public:

        bool DestroyMark = false;

        std::string Name;

        iNode(const char* name) : Name(name) {}
        friend class Children;
        virtual ~iNode() = default;

        bool IsInitialized() {

            return mInitialized;
        }

        // Chama o _Ready e marca o iNode como inicializado

        virtual void _Initialize() {

            mInitialized = true;
            _Ready();
        }

        // Marca o iNode para ser destruido no core [OBS] possivel erro se o node for destruido e depois algum node precisar dele

        void Destroy() {

            DestroyMark = true;
        }

        // Retorna o mParent, o parent foi colocado aqui ao invés de ficar no baseplate::children por motivos maiores

        template <typename T = iNode>
        T* GetParent() {

            return dynamic_cast<T*>(mParent);
        }

        // Cast seguro para outro tipo

        template<typename T>
        T* As() {

            return dynamic_cast<T*>(this);
        }

        //

        virtual void _Ready() = 0;
        virtual void _Event(SDL_Event& event) = 0;
        virtual void _Draw(GLuint vao, glm::mat4 projection) = 0;
        virtual void _Process(double delta) = 0;
        virtual void _Close() = 0;
    };
}