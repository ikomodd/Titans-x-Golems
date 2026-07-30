#include "Arena.hpp"

#include <fstream>
#include <algorithm>

#include "baseplate/data_models/model/RenderModel.hpp"

#include "game/instances/character/Character.hpp"
#include "game/instances/character/golem/Golem.hpp"
#include "game/instances/character/titan/Titan.hpp"

#include "game/managers/display/Display.hpp"
#include "game/instances/camera/Camera.hpp"

// [TODO] Esse arquivo ta muito grande e bem que poderia ser fragmentado

bool game::Arena::TestTileClicked(baseplate::Vector2 click_position, baseplate::Vector2i tile_position) {

    // OBS: Esse bloco de codigo foi feito pela IA Claude. Sorry, geometria não é comigo.

    // centro do losango na posição isométrica (sem o offset visual do debug rect)
    float tileCenterX = GetPosition().X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y);
    float tileCenterY = GetPosition().Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X);

    float dx = fabsf(click_position.X - tileCenterX);
    float dy = fabsf(click_position.Y - tileCenterY);

    // meio-eixos do losango (ajuste se a proporção real for diferente)
    float halfW = m_TileSize.X;
    float halfH = m_TileSize.Y;

    //

    if ((dx / halfW) + (dy / halfH) < 1.0f) {
        return true;
    }
    return false;
}

void game::Arena::SelectGolem(Golem* golem) {

    // Se ja tiver um character selecionado, deseleciona
    if (m_CurrentGolem)
        UnselectGolem();

    // seleciona
    m_CurrentGolem = golem;
}
 
void game::Arena::UnselectGolem() {

    m_CurrentGolem = nullptr;
}

bool game::Arena::CanMoveTo(baseplate::Vector2i tile) {

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

        Character* Character = node->As<game::Character>();
        if (Character && Character->mTilePosition == tile)
            return false;
    }
    return true;
}

void game::Arena::AttackTile(baseplate::Vector2i tile, float damage) {

    for (auto* node : GetChildren()) {

        Character* Character = node->As<game::Character>();
        if (Character && Character->mTilePosition == tile) {

            Character->GetDamage(damage);
        }
    }
}

//

void game::Arena::BuildArena() {

    std::ifstream File("../" + m_JsonPath);
    nlohmann::json Data = nlohmann::json::parse(File);

    m_TileSize = baseplate::Vector2(Data["tile_size"][0], Data["tile_size"][1]);
    m_TileSourceSize = baseplate::Vector2(Data["tile_source_size"][0], Data["tile_source_size"][1]);

    m_TileOffset = baseplate::Vector2(Data["tile_offset"][0], Data["tile_offset"][1]);

    DefineTextureAsset(Data["texture_name"]);

    DefineShaderAsset("block_shader");

    game::Camera::CurrentCamera->SetPosition(baseplate::Vector2((Data["map"][0].size() - 1) * m_TileSize.X, 0));

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    m_Tileset.clear();

    for (auto& [key, data] : Data["tileset"].items()) {

        int Id = data["id"];
        baseplate::Vector2 SourcePosition = baseplate::Vector2(data["position"][0], data["position"][1]);
        bool Obstacle = data["obstacle"];

        m_Tileset[Id] = new arena::Tile(SourcePosition, Obstacle);
    }

    // Converte o Tilemap em array JSON para o vetor 1D do m_Tilemap

    m_Tilemap.clear();

    for (size_t y = 0; y < Data["map"].size(); y++) {
        for (size_t x = 0; x < Data["map"][y].size(); x++) {

            int TileId = Data["map"][y][x];

            if (m_Tileset.contains(TileId))
                m_Tilemap.emplace_back(baseplate::Vector2i(x, y), TileId); // Cria valor X
        }
    }

    // Adiciona os Characters na arena

    if (!Builded) {

        std::cout << "Durante Build da arena: " << this << "\n";

        for (auto [key, character] : Data["characters"].items()) {

            std::string Type = character["type"];
            std::string Path = character["source"];
            baseplate::Vector2i TilePosition = baseplate::Vector2i((int)character["position"][0], (int)character["position"][1]);

            Character* Current = nullptr;

            if (Type == "golem")
                Current = new Golem(TilePosition, Path);
            else if (Type == "titan") 
                Current = new Titan(TilePosition, Path);

            AddNode(Current);
        }
    }

    Builded = true;
}

void game::Arena::PlayerRoundEnded() {

    for (auto* node : GetChildren()) {

        Golem* golem = node->As<Golem>();
        Titan* titan = node->As<Titan>();

        if (titan) {
            titan->RunIa();
            titan->mActions = titan->mActionsQuantity;
        }
        else if (golem)
            golem->mActions = golem->mActionsQuantity;
    }
    mCurrentRound++;
}

//

void game::Arena::_Ready() {

    mDisplayManager = &baseplate::Manager<game::DisplayManager>::Get();

    BuildArena();
}

void game::Arena::_Event(SDL_Event& event) {

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {

        baseplate::Vector2 ClickPosition = game::Camera::CurrentCamera->GetWorldPosition(baseplate::Vector2(event.button.x, event.button.y));

        // Passa por todos os tiles
        for (auto& [tile_position, tile_id] : m_Tilemap) {

            // Encontra o tile clicado
            if (TestTileClicked(ClickPosition, tile_position)) {

                bool HasGolemSelected = false;

                // Vê se a posição do tile clicado corresponde a algum golem
                for (auto* node : GetChildren()) {
                    auto* golem = node->As<Golem>();

                    // Verifica se é um character; se tem ações; se está na posição do tile clicado e se não é o character selecionado atual
                    if (golem && golem->mActions > 0 && golem->mTilePosition == tile_position && golem != m_CurrentGolem) {

                        HasGolemSelected = true;
                        SelectGolem(golem);
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
    else if (event.type == SDL_EVENT_KEY_DOWN) {

        SDL_Keymod ModState = SDL_GetModState();
        
        if (event.key.key == SDLK_RETURN) // Enter pula o turno
            PlayerRoundEnded();
        
        else if (ModState) {

            if (SDL_KMOD_ALT && event.key.key == SDLK_F3) // Alt + F3 reinicia a arena json (menos os characters)
                BuildArena();
        }
    }
}

void game::Arena::_Draw(GLuint vao, glm::mat4 projection) {

    game::Camera* CurrentCamera = game::Camera::CurrentCamera;
    mShaderAsset->Bind();

    for (auto [tile_position, tile_id] : m_Tilemap) {

        baseplate::Vector2 TilePosition(
            GetPosition().X + ((float)tile_position.X * m_TileSize.X + (float)tile_position.Y * m_TileSize.Y) - m_TileOffset.X,
            GetPosition().Y + ((float)tile_position.Y * m_TileSize.Y - (float)tile_position.X * m_TileSize.X) - m_TileOffset.Y
        );

        baseplate::Vector2 TileSize(
            m_TileSourceSize.X,
            m_TileSourceSize.Y
        );

        CurrentCamera->TransformToCameraView(TilePosition, TileSize);

        baseplate::base_glm::RenderModel Model(TilePosition, TileSize);

        //

        GLint MotionTileLoc = glGetUniformLocation(mShaderAsset->Program, "uIsMotionTile");
        if (m_CurrentGolem && m_CurrentGolem->TileIsInMotionDirections(tile_position))
            glUniform1i(MotionTileLoc, 1);
        else
            glUniform1i(MotionTileLoc, 0);

        GLint AttackTileLoc = glGetUniformLocation(mShaderAsset->Program, "uIsAttackTile");
        if (m_CurrentGolem && m_CurrentGolem->TileIsInAttackDirections(tile_position))
            glUniform1i(AttackTileLoc, 1);
        else
            glUniform1i(AttackTileLoc, 0);

        //

        GLint ProjectionLoc = glGetUniformLocation(mShaderAsset->Program, "uProjection");
        glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        Model.Bind(mShaderAsset->Program, "uModel");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureAsset->Texture);

        GLint TextureLoc = glGetUniformLocation(mShaderAsset->Program, "uTexture");
        glUniform1i(TextureLoc, 0);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
} 

void game::Arena::_Process(double delta) {

    std::sort(m_Tilemap.begin(), m_Tilemap.end(), [this](const auto& a, const auto& b) {

        float VisualA = (float)a.first.Y * m_TileSize.Y - (float)a.first.X * m_TileSize.X;
        float VisualB = (float)b.first.Y * m_TileSize.Y - (float)b.first.X * m_TileSize.X;
        return VisualA < VisualB;
    });
}