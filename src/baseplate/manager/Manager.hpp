#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

// ---------------------------------------------------------

class BSPLT_iManager {
protected:

    inline static std::vector<BSPLT_iManager*> m_Managers = {};
    BSPLT_iManager() {}
    virtual ~BSPLT_iManager() {}

public:

    //

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

    //

    virtual void _Init() {}
    virtual void _Event(SDL_Event& event) {}
    virtual void _Process() {}
    virtual void _Close() {}
};

// [] -----------------------------------------

template <typename T>
class BSPLT_Manager : public BSPLT_iManager {
public:

    std::string Name;

    //

    static T& Get() {

        static T ThisManager;
        static bool Registered = false;

        if (!Registered) {

            m_Managers.push_back(&ThisManager);
            Registered = true;

            std::cout << "[BASEPLATE_MANAGER] Manager adicionado: " << ThisManager.Name << "\n";
        }

        return ThisManager;
    }

protected:
    
    BSPLT_Manager(std::string name) : Name(name), BSPLT_iManager() {}
};