#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

#include "game/instances/arena/Arena.hpp"
#include "baseplate/data_models/model/RenderModel.hpp"

bool GAME_Character::TileIsInMotionDirections(Vector2i tile) {

    if (std::any_of(m_MotionDirections.begin(), m_MotionDirections.end(),
    [this, tile](const Vector2i& A) {

        Vector2i ActionTile = m_TilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

bool GAME_Character::TileIsInAttackDirections(Vector2i tile) {

    if (std::any_of(m_AttackDirections.begin(), m_AttackDirections.end(),
    [this, tile](const Vector2i& A) {

        Vector2i ActionTile = m_TilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

void GAME_Character::BuildCharacter() {

    std::ifstream File("../" + m_SourcePath);
    if (!File.is_open()) {
        std::cerr << "[GAME_Character] Erro ao abrir o arquivo: " << m_SourcePath << "\n";
        return;
    }

    nlohmann::json Data = nlohmann::json::parse(File);

    Name = Data["id"];

    m_Health          = Data["health"];
    m_Shield          = Data["shield"];
    m_Damage          = Data["damage"];
    m_ActionsQuantity = Data["actions"];

    m_Actions = m_ActionsQuantity + 1; // + 1 porque tem que conciderar o MoveTo quando o character é criado

    std::string TextureName = (Data["texture_name"] != "") ? Data["texture_name"] : "character_standart";
    DefineTextureAsset(TextureName);
    DefineShaderAsset("texture_shader");

    for (auto& [key, value] : Data["motion_directions"].items()) {

        m_MotionDirections.emplace_back(value[0], value[1]);
    }

    for (auto& [key, value] : Data["attack_directions"].items()) {

        m_AttackDirections.emplace_back(value[0], value[1]);
    }
}

void GAME_Character::MoveTo(Vector2i tile_position) {

    GAME_Arena* Arena = GetParent<GAME_Arena>();

    if (Arena->CanMoveTo(tile_position) && tile_position != m_TilePosition) {

        m_TilePosition = tile_position;
        SetPosition(Vector2(tile_position.X + tile_position.Y, tile_position.Y - tile_position.X) * Arena->GetTileSize());
    }

    m_Actions--;
}

void GAME_Character::AttackOn(Vector2i tile_position) {

    GAME_Arena* Arena = GetParent<GAME_Arena>();

    Arena->AttackTile(tile_position, m_Damage);

    m_Actions--;
}

void GAME_Character::GetDamage(float damage) {

    float CurrentDamage = damage - m_Shield;
    if (CurrentDamage < 0) CurrentDamage = 0;
    if (m_Shield > 0) m_Shield--;

    m_Health -= CurrentDamage;

    std::cout << "Character: " << Name << " foi atacado; Health: " << m_Health << " Shield: " << m_Shield << "\n";

    if (m_Health <= 0)
        Destroy();
}

//

void GAME_Character::_Ready() {

    BuildCharacter();
    MoveTo(m_SpawnPosition);
}

void GAME_Character::_Draw() {

    m_ShaderAsset->Bind();

    GAME_Camera* CurrentCamera = m_DisplayManager->GetCurrentCamera();
    Vector2 TextureSize = m_TextureAsset->TextureSize.ToVector2();

    Vector2 CharacterPosition = Vector2(GetPosition().X - TextureSize.X / 2, GetPosition().Y - TextureSize.Y);
    Vector2 CharacterSize = Vector2(TextureSize.X, TextureSize.Y);

    CurrentCamera->TransformToCameraView(CharacterPosition, CharacterSize);

    BSPLT_GLM_RenderModel Model(CharacterPosition, CharacterSize);
    Model.Bind(m_ShaderAsset->Program, "uModel");

    GLint ProjectionLoc = glGetUniformLocation(m_ShaderAsset->Program, "uProjection");
    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(m_DisplayManager->GetProjection()));

    //nesse contexto é inultil, mas manti para uma futura implementação
    Color4f BackgroundColorNormalized = BackgroundColor.Normalize();
    GLint BackgroundColorLoc = glGetUniformLocation(m_ShaderAsset->Program, "uBackgroundColor");
    glUniform4f(BackgroundColorLoc, BackgroundColorNormalized.R, BackgroundColorNormalized.G, BackgroundColorNormalized.B, BackgroundColorNormalized.A);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureAsset->Texture);

    GLint TextureLoc = glGetUniformLocation(m_ShaderAsset->Program, "uTexture");
    glUniform1i(TextureLoc, 0);

    glBindVertexArray(m_DisplayManager->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}