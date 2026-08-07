#include "Origin.hpp"

#include <iostream>

void game::Origin::Initialize() {

    std::cout << "[game::Origin] Inicializando origin: " << name << " { ";

    // Inicialização padrão do inode (obrigatório para override de Initialize)

    baseplate::iNode::Initialize();

    auto linearChildren = GetLinearChildren();

    for (baseplate::iNode* inode : linearChildren) {

        std::cout << "Iniciando " << inode->name << "... ";
        inode->Initialize();
        std::cout << inode->name << " finalizado; ";
    }

    std::cout << " }\n[game::Origin] origin inicializado com sucesso\n";
}