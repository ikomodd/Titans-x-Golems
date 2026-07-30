#include "State.hpp"

void GAME_GameState::_Initialize() {

    std::cout << "[GAME_GameState] Inicializando state: " << Name << " { ";

    baseplate::iNode::_Initialize();

    auto LinearChildren = GetLinearChildren();

    for (baseplate::iNode* inode : LinearChildren) {

        std::cout << "Iniciando " << inode->Name << "... ";
        inode->_Initialize();
        std::cout << inode->Name << " finalizado; ";
    }

    std::cout << " }\n[GAME_GameState] State inicializado com sucesso\n";
}