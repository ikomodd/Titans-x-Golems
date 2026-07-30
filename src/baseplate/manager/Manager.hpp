#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>


namespace baseplate {

    // iManager ----------------------------------------------------

    class iManager {
    protected:

        inline static std::vector<iManager*> m_Managers = {};

        iManager() {}
        virtual ~iManager() {}

    public:

        static void InitManagers() {

            for (auto* manager : m_Managers) {

                manager->_Init();
            }
        }

        static void CallEventManager(SDL_Event& event) {

            for (auto* manager : m_Managers) {

                manager->_Event(event);
            }
        }

        static void ProcessManagers() {

            for (auto* manager : m_Managers) {

                manager->_Process();
            }
        }

        static void CloseManagers() {

            for (auto* manager : m_Managers) {

                manager->_Close();
            }
        }

        virtual void _Init() = 0;
        virtual void _Event(SDL_Event& event) = 0;
        virtual void _Process() = 0;
        virtual void _Close() = 0;
    };

    // Manager -----------------------------------------

    template <typename T>
    class Manager : public iManager {
    public:

        std::string Name;

        //

        static T& Get() {

            static T ThisManager;
            static bool Registered = false;

            if (!Registered) {

                m_Managers.push_back(&ThisManager);
                Registered = true;

                std::cout << "[baseplate::Manager] Manager adicionado: " << ThisManager.Name << "\n";
            }

            return ThisManager;
        }

        void _Init() override {}
        void _Event(SDL_Event& event) override {}
        void _Process() override {}
        void _Close() override {}

    protected:
        
        Manager(std::string name) : Name(name), iManager() {}
    };
}