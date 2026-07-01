#include "Arena.hpp"

#include "game/managers/display/Display.hpp"
#include "game/managers/asset/Asset.hpp"
#include "game/instances/camera/Camera.hpp"

#include <fstream>
#include <algorithm>

void GAME_Arena::BuildArena() {

    GAME_AssetManager& AssetManager = BSPLT_Manager<GAME_AssetManager>::Get();

    std::ifstream File("../" + m_JsonPath);
    nlohmann::json Data = nlohmann::json::parse(File);

    m_TileSize = Vector2(Data["tile_size"][0], Data["tile_size"][1]);
    std::string TexturePath = Data["texture_path"];

    ASSET_TextureAsset* TextureAsset = AssetManager.GetTextureAsset("assets/Block.png");

    m_Texture = TextureAsset->Texture;
    m_Surface = TextureAsset->Surface;

    Position = Vector2(Data["map"][0].size() * m_TileSize.X * -1, 0);

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    for (auto& [key, data] : Data["tileset"].items()) {

        int Id = data["id"];
        Vector2 SourcePosition = Vector2(data["position"][0], data["position"][1]);
        Vector2 SourceSize = Vector2(data["size"][0], data["size"][1]);
        bool Collidible = data["is_collidible"];

        m_Tileset[Id] = new ARENA_Tile(SourcePosition, SourceSize, Collidible);
    }

    // Converte o Tilemap em array JSON para o vetor 2D do m_Tilemap

    for (size_t y = 0; y < Data["map"].size(); y++) {
        for (size_t x = 0; x < Data["map"][y].size(); x++) {

            int TileId = Data["map"][y][x];

            if (m_Tileset.contains(TileId))
                m_Tilemap.emplace_back(Vector2i(x, y), TileId); // Cria valor X
            else
                m_Tilemap.emplace_back(Vector2i(x, y), 0);
        }
    }
}

void GAME_Arena::_Ready() {

    m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();

    BuildArena();
}

void GAME_Arena::_Draw(SDL_Renderer* renderer, float viewport_scale) { // ESSE VIEWPORT SCALE TA DANDO PROBLEMA

    for (auto [tile_position, tile_id] : m_Tilemap) {

        if (tile_id != 0) {
            ARENA_Tile* Tile = m_Tileset[tile_id];

            GAME_Camera* CurrentCamera = m_DisplayManager->GetCurrentCamera();

            Vector2 TileSize = Tile->SourceSize;

            SDL_FRect TileRect = {
                Position.X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y),
                Position.Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X),
                TileSize.X,
                TileSize.Y
            };

            TileRect = CurrentCamera->GetRectCameraView(TileRect);

            SDL_FRect SourceRect = {
                Tile->SourcePosition.X,
                Tile->SourcePosition.Y,
                Tile->SourceSize.X,
                Tile->SourceSize.Y
            };

            SDL_RenderTexture(renderer, m_Texture, &SourceRect, &TileRect);
       }
    }
} 

void GAME_Arena::_Process(double delta) {

    std::sort(m_Tilemap.begin(), m_Tilemap.end(), [this](const auto& a, const auto& b) {

        float VisualA = (float)a.first.Y * m_TileSize.Y - (float)a.first.X * m_TileSize.X;
        float VisualB = (float)b.first.Y * m_TileSize.Y - (float)b.first.X * m_TileSize.X;
        return VisualA < VisualB;
    });
}