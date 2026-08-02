#include "State.hpp"

void game::GameState::Initialize() {

    std::cout << "[game::GameState] Inicializando state: " << name << " { ";

    // Inicialização padrão do inode (obrigatório para override de Initialize)

    baseplate::iNode::Initialize();

    auto linearChildren = GetLinearChildren();

    for (baseplate::iNode* inode : linearChildren) {

        std::cout << "Iniciando " << inode->name << "... ";
        inode->Initialize();
        std::cout << inode->name << " finalizado; ";
    }

    std::cout << " }\n[game::GameState] State inicializado com sucesso\n";
}