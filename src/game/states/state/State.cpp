#include "State.hpp"

void GAME_GameState::Initialize() {

    std::cout << "[GAME_GameState] Inicializando state: " << Name << " { ";

    _Ready();

    m_Initialized = true;

    auto LinearChildren = GetLinearChildren();

    for (BSPLT_Node* node : LinearChildren) {

        std::cout << "Iniciando " << node->Name << "... ";
        node->_Ready();
        std::cout << node->Name << " finalizado; ";
    }

    std::cout << " }\n[GAME_GameState] State inicializado com sucesso\n";
}