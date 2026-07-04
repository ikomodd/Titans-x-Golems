#include "Arena.hpp"

#include <fstream>
#include <algorithm>

#include "game/instances/character/Character.hpp"

bool GAME_Arena::TestTileClicked(Vector2 click_position, Vector2i tile_position) {

    // OBS: Esse bloco de codigo foi feito pela IA Claude. Sorry, geometria não é comigo.

    // centro do losango na posição isométrica (sem o offset visual do debug rect)
    float tileCenterX = Position.X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y);
    float tileCenterY = Position.Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X);

    float dx = fabsf(click_position.X - tileCenterX);
    float dy = fabsf(click_position.Y - tileCenterY);

    // meio-eixos do losango (ajuste se a proporção real for diferente)
    float halfW = m_TileSize.X;
    float halfH = m_TileSize.Y;

    // rect de debug continua só como referência visual
    // SDL_FRect Rect = {
    //     tileCenterX - m_TileOffset.X * 0.5f,
    //     tileCenterY - m_TileOffset.Y * 0.5f,
    //     m_TileOffset.X,
    //     m_TileOffset.Y
    // };
    // m_DisplayManager->GetCurrentCamera()->DrawRect(Rect);

    //

    if ((dx / halfW) + (dy / halfH) < 1.0f) {
        return true;
    }
    return false;
}

void GAME_Arena::SelectCharacter(GAME_Character* character) {

    character->m_CurrentRound = m_CurrentRound;

    // Se ja tiver um character selecionado, deseleciona
    if (m_CharacterSelected)
    UnselectCharacter();

    // seleciona
    m_CharacterSelected = character;
    character->Select();
}

void GAME_Arena::UnselectCharacter() {

    m_CharacterSelected->Unselect();
    m_CharacterSelected = nullptr;
}

//

void GAME_Arena::BuildArena() {

    std::ifstream File("../" + m_JsonPath);
    nlohmann::json Data = nlohmann::json::parse(File);

    m_TileSize = Vector2(Data["tile_size"][0], Data["tile_size"][1]);
    m_TileSourceSize = Vector2(Data["tile_source_size"][0], Data["tile_source_size"][1]);

    m_TileOffset = Vector2(Data["tile_offset"][0], Data["tile_offset"][1]);

    LoadTexture(Data["texture_path"]);

    m_DisplayManager->GetCurrentCamera()->Position = Vector2((Data["map"][0].size() - 1) * m_TileSize.X, 0);

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    for (auto& [key, data] : Data["tileset"].items()) {

        int Id = data["id"];
        Vector2 SourcePosition = Vector2(data["position"][0], data["position"][1]);
        bool Collidible = data["is_collidible"];

        m_Tileset[Id] = new ARENA_Tile(SourcePosition, Collidible);
    }

    // Converte o Tilemap em array JSON para o vetor 1D do m_Tilemap

    for (size_t y = 0; y < Data["map"].size(); y++) {
        for (size_t x = 0; x < Data["map"][y].size(); x++) {

            int TileId = Data["map"][y][x];

            if (m_Tileset.contains(TileId))
                m_Tilemap.emplace_back(Vector2i(x, y), TileId); // Cria valor X
        }
    }
}

void GAME_Arena::PlayerRoundEnded() {

    for (auto* node : GetChildren()) {
        GAME_Character* Character = node->As<GAME_Character>();

        if (Character && !Character->m_PlayerOwner) {

            Character->RunIa();
        }
    }

    m_CurrentRound++;
}

//

void GAME_Arena::_Ready() {

    BuildArena();
}

void GAME_Arena::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {

        Vector2 LogicalPosition = 0;
        SDL_RenderCoordinatesFromWindow(m_DisplayManager->Renderer, event.button.x, event.button.y, &LogicalPosition.X, &LogicalPosition.Y);
        Vector2 ClickPosition = m_DisplayManager->GetCurrentCamera()->GetWorldPosition(LogicalPosition);

        // Passa por todos os tiles
        for (auto& [tile_position, tile_id] : m_Tilemap) {

            // Encontra o tile clicado
            if (TestTileClicked(ClickPosition, tile_position)) {

                bool CharacterSelected = false;

                // Vê se a posição do tile clicado corresponde a algum character
                for (auto* node : GetChildren()) {
                    auto* Character = node->As<GAME_Character>();

                    // Verifica se é um character; se a ultima ação foi nesse round; se está na posição do tile clicado; se não é o character selecionado atual e se ele pertence ao player
                    if (Character && m_CurrentRound > Character->m_CurrentRound && Character->m_TilePosition == tile_position && Character != m_CharacterSelected && Character->m_PlayerOwner) {

                        CharacterSelected = true;
                        SelectCharacter(Character);
                    }
                }
                
                // se nenhum tile for selecionado; se tem um character selecionado e se o a posição do tile ta presente na ActionDirections do character selecionado, executa a ação do character e deseleciona
                if (m_CharacterSelected && !CharacterSelected && m_CharacterSelected->TileIsInActionDirections(tile_position)) {

                    m_CharacterSelected->TileSelected(tile_position);
                    UnselectCharacter();
                }
                break;
            }
        }
    }
    else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_RETURN)
        PlayerRoundEnded();
}

void GAME_Arena::_Draw(SDL_Renderer* renderer) {

    for (auto [tile_position, tile_id] : m_Tilemap) {

        bool IsActionTile = false;        

        if (m_CharacterSelected && m_CharacterSelected->TileIsInActionDirections(tile_position))
            IsActionTile = true;

        if (tile_id != 0) {
            ARENA_Tile* Tile = m_Tileset[tile_id];

            GAME_Camera* CurrentCamera = m_DisplayManager->GetCurrentCamera();

            SDL_FRect TileRect = {
                Position.X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y) - m_TileOffset.X,
                Position.Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X) - m_TileOffset.Y,
                m_TileSourceSize.X,
                m_TileSourceSize.Y
            };

            TileRect = CurrentCamera->GetRectCameraView(TileRect);

            SDL_FRect SourceRect = {
                Tile->SourcePosition.X,
                Tile->SourcePosition.Y,
                m_TileSourceSize.X,
                m_TileSourceSize.Y
            };
            if (IsActionTile)
                SourceRect.x += m_TileSourceSize.X;

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