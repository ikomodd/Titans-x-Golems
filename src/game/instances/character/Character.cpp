#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

#include "game/instances/arena/Arena.hpp"
#include "baseplate/data_models/model/RenderModel.hpp"

#include "game/managers/display/Display.hpp"
#include "game/instances/camera/Camera.hpp"

bool game::Character::TileIsInMotionDirections(baseplate::Vector2i tile) {

    // OBS: isso serve pra verificar algo em um vector

    if (std::any_of(m_motionDirections.begin(), m_motionDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i actionTile = m_tilePosition + A;
        return actionTile.X == tile.X && actionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

bool game::Character::TileIsInAttackDirections(baseplate::Vector2i tile) {

    if (std::any_of(m_attackDirections.begin(), m_attackDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i actionTile = m_tilePosition + A;
        return actionTile.X == tile.X && actionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

void game::Character::BuildCharacter() {

    std::ifstream file("../" + m_sourcePath);
    if (!file.is_open()) {
        std::cerr << "[game::Character] Erro ao abrir o arquivo: " << m_sourcePath << "\n";
        return;
    }

    nlohmann::json data = nlohmann::json::parse(file);

    name = data["id"];

    m_health          = data["health"];
    m_shield          = data["shield"];
    m_damage          = data["damage"];
    m_actionsQuantity = data["actions"];

    m_actions = m_actionsQuantity;

    m_attackCost = data["attack_cost"];
    m_motionCost = data["motion_cost"];

    std::string textureName = (data["texture_name"] != "") ? data["texture_name"] : "character_standart";
    DefineTextureAsset(textureName);
    DefineShaderAsset("texture_shader");

    for (auto& [key, value] : data["motion_directions"].items()) {

        m_motionDirections.emplace_back(value[0], value[1]);
    }

    for (auto& [key, value] : data["attack_directions"].items()) {

        m_attackDirections.emplace_back(value[0], value[1]);
    }
}

bool game::Character::MoveTo(baseplate::Vector2i tile_position, bool free) {

    Arena* arena = GetParent<Arena>();

    if (m_actions - m_motionCost >= 0 && arena->IsAValidTile(tile_position) && tile_position != m_tilePosition) {

        m_tilePosition = tile_position;
        SetPosition(baseplate::Vector2(tile_position.X + tile_position.Y, tile_position.Y - tile_position.X) * arena->GetTileSize());
        
        if (!free)
            m_actions -= m_motionCost;

        std::cout << m_actions << "\n";

        // Retorna o resultado

        return true;
    }
    return false;
}

bool game::Character::AttackOn(baseplate::Vector2i tile_position) {

    Arena* arena = GetParent<Arena>();

    if (m_actions - m_attackCost >= 0) {

        arena->AttackTile(tile_position, m_damage);
        m_actions -= m_attackCost;

        // Retorna o resultado

        return true;
    }
    return false;
}

void game::Character::GetDamage(float damage) {

    float currentDamage = damage - m_shield;
    if (currentDamage < 0) currentDamage = 0;
    if (m_shield > 0) m_shield--;

    m_health -= currentDamage;

    std::cout << "Character: " << name << " foi atacado; Health: " << m_health << " Shield: " << m_shield << "\n";

    if (m_health <= 0)
        Destroy();
}

//

void game::Character::Ready() {

    m_displayManager = &baseplate::Manager<game::DisplayManager>::Get();

    BuildCharacter();
    MoveTo(m_spawnPosition, true);
}

void game::Character::Draw(GLuint vao, glm::mat4 projection) {

    m_shaderAsset->Bind();

    game::Camera* currentCamera = Camera::currentCamera;
    baseplate::Vector2 textureSize = m_textureAsset->textureSize.ToVector2();

    baseplate::Vector2 characterPosition(GetPosition().X - textureSize.X / 2, GetPosition().Y - textureSize.Y);
    baseplate::Vector2 characterSize(textureSize.X, textureSize.Y);

    currentCamera->TransformToCameraView(characterPosition, characterSize);

    baseplate::base_glm::RenderModel model(characterPosition, characterSize);
    model.Bind(m_shaderAsset->program, "uModel");

    GLint projectionLoc = glGetUniformLocation(m_shaderAsset->program, "uProjection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //nesse contexto é inultil, mas manti para uma futura implementação
    baseplate::Color4f backgroundColorNormalized = backgroundColor.Normalize();
    GLint backgroundColorLoc = glGetUniformLocation(m_shaderAsset->program, "uBackgroundColor");
    glUniform4f(backgroundColorLoc, backgroundColorNormalized.R, backgroundColorNormalized.G, backgroundColorNormalized.B, backgroundColorNormalized.A);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureAsset->texture);

    GLint textureLoc = glGetUniformLocation(m_shaderAsset->program, "uTexture");
    glUniform1i(textureLoc, 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}