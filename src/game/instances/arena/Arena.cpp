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

bool game::Arena::TestTileClicked(Vector2 click_position, Vector2i tile_position) {

    // OBS: Esse bloco de codigo foi feito pela IA Claude. Sorry, geometria não é comigo.

    // centro do losango na posição isométrica (sem o offset visual do debug rect)
    float tileCenterX = GetPosition().X + ((float)tile_position.X * m_tileSize.X + (float)tile_position.Y * m_tileSize.Y);
    float tileCenterY = GetPosition().Y + ((float)tile_position.Y * m_tileSize.Y - (float)tile_position.X * m_tileSize.X);

    float dx = fabsf(click_position.X - tileCenterX);
    float dy = fabsf(click_position.Y - tileCenterY);

    // meio-eixos do losango (ajuste se a proporção real for diferente)
    float halfW = m_tileSize.X;
    float halfH = m_tileSize.Y;

    //

    if ((dx / halfW) + (dy / halfH) < 1.0f) {
        return true;
    }
    return false;
}

void game::Arena::SelectGolem(Golem* golem) {

    // Se ja tiver um character selecionado, deseleciona

    if (m_currentGolem)
        UnselectGolem();

    // seleciona
    m_currentGolem = golem;
}
 
void game::Arena::UnselectGolem() {

    m_currentGolem = nullptr;
}

bool game::Arena::CanMoveTo(Vector2i tile) {

    bool isValid = false;

    // Ve se o tile é valido
    for (auto& [tile_position, tile_id] : m_tilemap)  {

        if (tile_position == tile && !m_tileset[tile_id]->Obstacle) {
            isValid = true;
            break;
        }
    }

    if (!isValid)
        return false;

    // Vê se tem algum character no tile
    for (auto* node : GetChildren()) {

        Character* character = node->As<game::Character>();
        if (character && character->m_tilePosition == tile)
            return false;
    }
    return true;
}

void game::Arena::AttackTile(Vector2i tile, float damage) {

    for (auto* node : GetChildren()) {

        Character* character = node->As<game::Character>();
        if (character && character->m_tilePosition == tile) {

            character->GetDamage(damage);
        }
    }
}

bool game::Arena::IsAValidTile(Vector2i tile, bool ignore_characters) {

    bool result = true;

    // Se está dentro do mapa

    if (!(tile.X >= 0 && tile.X <= m_mapSize.X && tile.Y >= 0 && tile.Y <= m_mapSize.Y))
        result = false;

    // Se é colidível

        // dps
    
    // Se tem alguem em cima

    if (!ignore_characters) {
        for (auto* child_node : GetChildren()) {

            Character* character = child_node->As<Character>();
            if (character && character->m_tilePosition == tile) {

                result = false;
                break;
            }
        }
    }

    return result;
}

//

void game::Arena::BuildArena() {

    std::ifstream file("../" + m_jsonPath);
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();

    m_tileSize = baseplate::Vector2(data["tile_size"][0], data["tile_size"][1]);
    m_tileSourceSize = baseplate::Vector2(data["tile_source_size"][0], data["tile_source_size"][1]);
    m_tileOffset = baseplate::Vector2(data["tile_offset"][0], data["tile_offset"][1]);

    m_mapSize = baseplate::Vector2i(data["map_size"][0], data["map_size"][1]);

    DefineTextureAsset(data["texture_name"]);

    DefineShaderAsset("block_shader");

    game::Camera::currentCamera->SetPosition(baseplate::Vector2((data["map"][0].size() - 1) * m_tileSize.X, 0));

    // Converte o Tileset em dictionary JSON para o vetor de m_Tileset

    m_tileset.clear();

    for (auto& [key, value] : data["tileset"].items()) {

        int id = value["id"];
        baseplate::Vector2 sourcePosition = baseplate::Vector2(value["position"][0], value["position"][1]);
        bool obstacle = value["obstacle"];

        m_tileset[id] = new arena::Tile(sourcePosition, obstacle);
    }

    // Converte o Tilemap em array JSON para o vetor 1D do m_Tilemap

    m_tilemap.clear();

    for (size_t y = 0; y < data["map"].size(); y++) {
        for (size_t x = 0; x < data["map"][y].size(); x++) {

            int tileId = data["map"][y][x];

            if (m_tileset.contains(tileId))
                m_tilemap.emplace_back(baseplate::Vector2i(x, y), tileId); // Cria valor X
        }
    }

    // Adiciona os Characters na arena

    if (!m_builded) {
        
        std::cout << "Durante Build da arena: " << this << "\n";

        for (auto [key, value] : data["characters"].items()) {

            std::string type = value["type"];
            std::string path = value["source"];
            baseplate::Vector2i tilePosition = baseplate::Vector2i((int)value["position"][0], (int)value["position"][1]);

            Character* current = nullptr;

            if (type == "golem")
                current = new Golem(tilePosition, path);
            else if (type == "titan") 
                current = new Titan(tilePosition, path);

            AddNode(current);
        }
    }

    m_builded = true;
}

void game::Arena::PlayerRoundEnded() {

    for (auto* node : GetChildren()) {

        Golem* golem = node->As<Golem>();
        Titan* titan = node->As<Titan>();

        if (titan) {
            titan->RunIa();
            titan->m_actions = titan->m_actionsQuantity;
        }
        else if (golem)
            golem->m_actions = golem->m_actionsQuantity;
    }
    m_currentRound++;
}

//

void game::Arena::Ready() {

    m_displayManager = &baseplate::Manager<game::DisplayManager>::Get();

    BuildArena();
}

void game::Arena::Event(const SDL_Event& event) {

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {

        baseplate::Vector2 clickPosition = Camera::currentCamera->GetWorldPosition(baseplate::Vector2(event.button.x, event.button.y));

        // Passa por todos os tiles
        for (auto& [tile_position, tile_id] : m_tilemap) {

            // Encontra o tile clicado
            if (TestTileClicked(clickPosition, tile_position)) {

                bool hasGolemSelected = false;

                // Vê se a posição do tile clicado corresponde a algum golem
                for (auto* node : GetChildren()) {
                    auto* golem = node->As<Golem>();

                    // Verifica se é um character; se tem ações; se está na posição do tile clicado e se não é o character selecionado atual
                    if (golem && golem->m_actions > 0 && golem->m_tilePosition == tile_position && golem != m_currentGolem) {

                        hasGolemSelected = true;
                        SelectGolem(golem);
                    }
                }
                
                // se nenhum tile for selecionado; se tem um character selecionado e se o a posição do tile ta presente na ActionDirections do character selecionado, executa a ação do character e deseleciona
                if (m_currentGolem && !hasGolemSelected) {

                    if (m_currentGolem->TileIsInMotionDirections(tile_position)) {
                        m_currentGolem->MoveTo(tile_position);
                        UnselectGolem();
                    }
                    else if (m_currentGolem->TileIsInAttackDirections(tile_position)) {
                        m_currentGolem->AttackOn(tile_position);
                        UnselectGolem();
                    }
                }
                break;
            }
        }
    }
    else if (event.type == SDL_EVENT_KEY_DOWN) {

        SDL_Keymod modState = SDL_GetModState();
        
        if (event.key.key == SDLK_RETURN) // Enter pula o turno
            PlayerRoundEnded();
        
        else if (modState) {

            if (SDL_KMOD_ALT && event.key.key == SDLK_F3) // Alt + F3 reinicia a arena json (menos os characters)
                BuildArena();
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_MOTION) {

        bool hasTarget = false;
        baseplate::Vector2 mousePosition = Camera::currentCamera->GetWorldPosition(baseplate::Vector2(event.motion.x, event.motion.y));

        for (auto [tile_position, tile_id] : m_tilemap) {

            if (TestTileClicked(mousePosition, tile_position)) {

                for (auto* inode : GetChildren()) {

                    auto* titan = inode->As<Titan>();
                    if (titan && titan->m_tilePosition == tile_position) {

                        m_titanInMouseTarget = titan;
                        hasTarget = true;
                        break;
                    }
                }
            }
        }

        if (!hasTarget)
            m_titanInMouseTarget = nullptr;
    }
}

void game::Arena::Draw(GLuint vao, glm::mat4 projection) {

    game::Camera* currentCamera = game::Camera::currentCamera;
    m_shaderAsset->Bind();

    for (auto [tile_position, tile_id] : m_tilemap) {

        baseplate::Vector2 tilePosition(
            GetPosition().X + ((float)tile_position.X * m_tileSize.X + (float)tile_position.Y * m_tileSize.Y) - m_tileOffset.X,
            GetPosition().Y + ((float)tile_position.Y * m_tileSize.Y - (float)tile_position.X * m_tileSize.X) - m_tileOffset.Y
        );

        baseplate::Vector2 tileSize(
            m_tileSourceSize.X,
            m_tileSourceSize.Y
        );

        currentCamera->TransformToCameraView(tilePosition, tileSize);

        baseplate::base_glm::RenderModel model(tilePosition, tileSize);

        // Da destaque nos tiles referentes ao Golem selecionado

        GLint motionTileLoc = glGetUniformLocation(m_shaderAsset->program, "uIsMotionTile");
        GLint attackTileLoc = glGetUniformLocation(m_shaderAsset->program, "uIsAttackTile");

        if (m_currentGolem && m_currentGolem->TileIsInMotionDirections(tile_position) || m_titanInMouseTarget && m_titanInMouseTarget->TileIsInMotionDirections(tile_position))
            glUniform1i(motionTileLoc, 1);
        else
            glUniform1i(motionTileLoc, 0);

        if (m_currentGolem && m_currentGolem->TileIsInAttackDirections(tile_position) || m_titanInMouseTarget && m_titanInMouseTarget->TileIsInAttackDirections(tile_position))
             glUniform1i(attackTileLoc, 1);
        else
            glUniform1i(attackTileLoc, 0);

        //

        GLint projectionLoc = glGetUniformLocation(m_shaderAsset->program, "uProjection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, ::glm::value_ptr(projection));

        model.Bind(m_shaderAsset->program, "uModel");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureAsset->texture);

        GLint textureLoc = glGetUniformLocation(m_shaderAsset->program, "uTexture");
        glUniform1i(textureLoc, 0);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
} 

void game::Arena::Process(double delta) {

    std::sort(m_tilemap.begin(), m_tilemap.end(), [this](const auto& a, const auto& b) {

        float visualA = (float)a.first.Y * m_tileSize.Y - (float)a.first.X * m_tileSize.X;
        float visualB = (float)b.first.Y * m_tileSize.Y - (float)b.first.X * m_tileSize.X;
        return visualA < visualB;
    });
}