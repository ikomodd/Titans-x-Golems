#include "Arena.hpp"

#include "game/managers/display/Display.hpp"

#include <fstream>

void GAME_Arena::BuildArena() {

    GAME_DisplayManager& DisplayManager = BSPLT_Manager<GAME_DisplayManager>::Get();

    std::ifstream File("../" + m_JsonPath);
    nlohmann::json Data = nlohmann::json::parse(File);

    m_TileSize = Vector2(Data["tile_size"][0], Data["tile_size"][1]);
    m_OffsetPosition = DisplayManager.GetWindowSize() / 2 - Vector2(Data["map"][0].size() * m_TileSize.X, Data["map"].size() * m_TileSize.Y) / 2;

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    for (auto& [key, data] : Data["tileset"].items()) {

        int Id = data["id"];
        Vector2i SourcePosition = Vector2i(data["position"][0], data["position"][1]);
        Vector2i SourceSize = Vector2i(data["size"][0], data["size"][1]);
        bool Collidible = data["is_collidible"];

        m_Tileset[Id] = new ARENA_Tile(SourcePosition, SourceSize, Collidible);
    }

    // Converte o Tilemap em array JSON para o vetor 2D do m_Tilemap

    for (size_t y = 0; y < Data["map"].size(); y++) {
        m_Tilemap.emplace_back(); // Cria layer Y

        for (size_t x = 0; x < Data["map"][y].size(); x++) {

            int TileId = Data["map"][y][x];

            if (m_Tileset.contains(TileId))
                m_Tilemap[y].push_back(TileId); // Cria valor X
            else
                m_Tilemap[y].push_back(0);
        }
    }
}

void GAME_Arena::_Ready() {

    BuildArena();
}

void GAME_Arena::_Draw(SDL_Renderer* renderer) {

    for (size_t y = 0; y < m_Tilemap.size(); y++) {
        for (size_t x = 0; x < m_Tilemap[y].size(); x++) {
            int& TileId = m_Tilemap[y][x];

            if (TileId != 0) {
                ARENA_Tile* Tile = m_Tileset[TileId];

                SDL_FRect TileRect = {
                    m_OffsetPosition.X + x * m_TileSize.X + y * m_TileSize.Y,
                    m_OffsetPosition.Y + y * m_TileSize.Y - x * m_TileSize.X,
                    16,
                    16
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &TileRect);
            }
        }
    }
} 