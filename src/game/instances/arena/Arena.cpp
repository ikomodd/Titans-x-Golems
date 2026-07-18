#include "Arena.hpp"

#include <fstream>
#include <algorithm>

#include "baseplate/data_models/model/RenderModel.hpp"

#include "game/instances/character/Character.hpp"
#include "game/instances/character/golem/Golem.hpp"
#include "game/instances/character/titan/Titan.hpp"

bool GAME_Arena::TestTileClicked(Vector2 click_position, Vector2i tile_position) {

    // OBS: Esse bloco de codigo foi feito pela IA Claude. Sorry, geometria não é comigo.

    // centro do losango na posição isométrica (sem o offset visual do debug rect)
    float tileCenterX = GetPosition().X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y);
    float tileCenterY = GetPosition().Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X);

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

void GAME_Arena::SelectGolem(GAME_Golem* golem) {

    // Se ja tiver um character selecionado, deseleciona
    if (m_CurrentGolem)
        UnselectGolem();

    // seleciona
    m_CurrentGolem = golem;
}
 
void GAME_Arena::UnselectGolem() {

    m_CurrentGolem = nullptr;
}

bool GAME_Arena::CanMoveTo(Vector2i tile) {

    bool IsValid = false;

    

    // Ve se o tile é valido
    for (auto& [tile_position, tile_id] : m_Tilemap)  {

        if (tile_position == tile && !m_Tileset[tile_id]->Obstacle) {
            IsValid = true;
            break;
        }
    }

    if (!IsValid)
        return false;

    // Vê se tem algum character no tile
    for (auto* node : GetChildren()) {

        GAME_Character* Character = node->As<GAME_Character>();
        if (Character && Character->m_TilePosition == tile)
            return false;
    }
    return true;
}

void GAME_Arena::AttackTile(Vector2i tile, float damage) {

    for (auto* node : GetChildren()) {

        GAME_Character* Character = node->As<GAME_Character>();
        if (Character && Character->m_TilePosition == tile) {

            Character->GetDamage(damage);
        }
    }
}

//

void GAME_Arena::BuildArena() {

    std::ifstream File("../" + m_JsonPath);
    nlohmann::json Data = nlohmann::json::parse(File);

    m_TileSize = Vector2(Data["tile_size"][0], Data["tile_size"][1]);
    m_TileSourceSize = Vector2(Data["tile_source_size"][0], Data["tile_source_size"][1]);

    m_TileOffset = Vector2(Data["tile_offset"][0], Data["tile_offset"][1]);

    LoadTexture(Data["texture_path"]);

    LoadShader("assets/shaders/block/BlockShader.vert", "assets/shaders/block/BlockShader.frag");

    m_DisplayManager->GetCurrentCamera()->SetPosition(Vector2((Data["map"][0].size() - 1) * m_TileSize.X, 0));

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    for (auto& [key, data] : Data["tileset"].items()) {

        int Id = data["id"];
        Vector2 SourcePosition = Vector2(data["position"][0], data["position"][1]);
        bool Obstacle = data["obstacle"];

        m_Tileset[Id] = new ARENA_Tile(SourcePosition, Obstacle);
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

        GAME_Golem* Golem = node->As<GAME_Golem>();
        GAME_Titan* Titan = node->As<GAME_Titan>();

        if (Titan) {
            Titan->RunIa();
            Titan->m_Actions = Titan->m_ActionsQuantity;
        }
        else if (Golem)
            Golem->m_Actions = Golem->m_ActionsQuantity;
    }
    m_CurrentRound++;
}

//

void GAME_Arena::_Ready() {

    BuildArena();
}

void GAME_Arena::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {

        Vector2 ClickPosition = m_DisplayManager->GetCurrentCamera()->GetWorldPosition(Vector2(event.button.x, event.button.y));

        // Passa por todos os tiles
        for (auto& [tile_position, tile_id] : m_Tilemap) {

            // Encontra o tile clicado
            if (TestTileClicked(ClickPosition, tile_position)) {

                bool HasGolemSelected = false;

                // Vê se a posição do tile clicado corresponde a algum golem
                for (auto* node : GetChildren()) {
                    auto* Golem = node->As<GAME_Golem>();

                    // Verifica se é um character; se tem ações; se está na posição do tile clicado e se não é o character selecionado atual
                    if (Golem && Golem->m_Actions > 0 && Golem->m_TilePosition == tile_position && Golem != m_CurrentGolem) {

                        HasGolemSelected = true;
                        SelectGolem(Golem);
                    }
                }
                
                // se nenhum tile for selecionado; se tem um character selecionado e se o a posição do tile ta presente na ActionDirections do character selecionado, executa a ação do character e deseleciona
                if (m_CurrentGolem && !HasGolemSelected) {

                    if (m_CurrentGolem->TileIsInMotionDirections(tile_position)) {
                        m_CurrentGolem->MoveTo(tile_position);
                        UnselectGolem();
                    }
                    else if (m_CurrentGolem->TileIsInAttackDirections(tile_position)) {
                        m_CurrentGolem->AttackOn(tile_position);
                        UnselectGolem();
                    }
                }
                break;
            }
        }
    }
    else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_RETURN)
        PlayerRoundEnded();
}

void GAME_Arena::_Draw() {

    GAME_Camera* CurrentCamera = m_DisplayManager->GetCurrentCamera();
    m_ShaderAsset->Bind();

    for (auto [tile_position, tile_id] : m_Tilemap) {

        Vector2 TilePosition = Vector2(
            GetPosition().X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y) - m_TileOffset.X,
            GetPosition().Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X) - m_TileOffset.Y
        );

        Vector2 TileSize = Vector2(
            m_TileSourceSize.X,
            m_TileSourceSize.Y
        );

        CurrentCamera->TransformToCameraView(TilePosition, TileSize);

        BSPLT_GLM_RenderModel Model(TilePosition, TileSize);

        //

        GLint MotionTileLoc = glGetUniformLocation(m_ShaderAsset->Program, "uIsMotionTile");
        if (m_CurrentGolem && m_CurrentGolem->TileIsInMotionDirections(tile_position))
            glUniform1i(MotionTileLoc, 1);
        else
            glUniform1i(MotionTileLoc, 0);

        GLint AttackTileLoc = glGetUniformLocation(m_ShaderAsset->Program, "uIsAttackTile");
        if (m_CurrentGolem && m_CurrentGolem->TileIsInAttackDirections(tile_position))
            glUniform1i(AttackTileLoc, 1);
        else
            glUniform1i(AttackTileLoc, 0);

        //

        GLint ProjectionLoc = glGetUniformLocation(m_ShaderAsset->Program, "uProjection");
        glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(m_DisplayManager->GetProjection()));

        Model.Bind(m_ShaderAsset->Program, "uModel");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureAsset->Texture);

        GLint TextureLoc = glGetUniformLocation(m_ShaderAsset->Program, "uTexture");
        glUniform1i(TextureLoc, 0);

        glBindVertexArray(m_DisplayManager->GetVAO());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
} 

void GAME_Arena::_Process(double delta) {

    std::sort(m_Tilemap.begin(), m_Tilemap.end(), [this](const auto& a, const auto& b) {

        float VisualA = (float)a.first.Y * m_TileSize.Y - (float)a.first.X * m_TileSize.X;
        float VisualB = (float)b.first.Y * m_TileSize.Y - (float)b.first.X * m_TileSize.X;
        return VisualA < VisualB;
    });
}