#include "Arena.hpp"

#include <map>
#include <queue>
#include <algorithm>

#include "game/instances/character/Character.hpp"

std::vector<baseplate::Vector2i> game::Arena::MakeBFS(Character* character, Vector2i origin, Vector2i target) {

    // atual, anterior
    std::map<Vector2i, Vector2i> visited;
    std::queue<Vector2i> tileQueue;

    tileQueue.push(origin);
    visited[origin] = origin;

    while (!tileQueue.empty()) {

        Vector2i current = tileQueue.front();
        tileQueue.pop();

        //std::cout << "Processando: " << current.ToString() << " Queue: " << tileQueue.size() << " Visited: " << visited.size() << "\n";

        for (Vector2i motion_direction : character->m_motionDirections) {

            Vector2i mapPosition = current + motion_direction;

            // Vê se o tile não foi visitado e se ele é válido

            if (!visited.contains(mapPosition) && IsAValidTile(mapPosition)) {

                // Adiciona na queue e em visitados

                tileQueue.push(mapPosition);
                visited[mapPosition] = current;

                // Vê se o tile é o destino e depois faz o caminho inverso para achar o caminho

                if (mapPosition == target) {

                    std::vector<Vector2i> endPath;
            
                    Vector2i step = target;
                    while (true) {

                        if (visited[step] != step) {

                            endPath.push_back(step);
                            step = visited[step];
                        }
                        else
                            break;
                    }

                    // Desinverte e retorna o caminho finalizado

                    std::reverse(endPath.begin(), endPath.end());
                    return endPath;
                }
            }
        }
    }

    return {};
}