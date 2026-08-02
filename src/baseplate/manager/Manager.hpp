#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>


namespace baseplate {

    // iManager ----------------------------------------------------

    class iManager {
    protected:

        inline static std::vector<iManager*> m_managers = {};

        iManager() {}
        virtual ~iManager() {}

    public:

        static void InitManagers() {

            for (auto* manager : m_managers) {

                manager->Init();
            }
        }

        static void CallEventManager(SDL_Event& event) {

            for (auto* manager : m_managers) {

                manager->Event(event);
            }
        }

        static void ProcessManagers() {

            for (auto* manager : m_managers) {

                manager->Process();
            }
        }

        static void CloseManagers() {

            for (auto* manager : m_managers) {

                manager->Close();
            }
        }

        virtual void Init() = 0;
        virtual void Event(const SDL_Event& event) = 0;
        virtual void Process() = 0;
        virtual void Close() = 0;
    };

    // Manager -----------------------------------------

    template <typename T>
    class Manager : public iManager {
    public:

        std::string name;

        //

        static T& Get() {

            static T thisManager;
            static bool registered = false;

            if (!registered) {

                m_managers.push_back(&thisManager);
                registered = true;

                std::cout << "[baseplate::Manager] Manager adicionado: " << thisManager.name << "\n";
            }

            return thisManager;
        }

        void Init() override {}
        void Event(const SDL_Event& event) override {}
        void Process() override {}
        void Close() override {}

    protected:
        
        Manager(std::string name) : name(name), iManager() {}
    };
}