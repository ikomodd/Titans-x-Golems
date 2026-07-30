#include "Character.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

#include "game/instances/arena/Arena.hpp"
#include "baseplate/data_models/model/RenderModel.hpp"

#include "game/managers/display/Display.hpp"
#include "game/instances/camera/Camera.hpp"

bool GAME_Character::TileIsInMotionDirections(baseplate::Vector2i tile) {

    // OBS: isso serve pra verificar algo em um vector

    if (std::any_of(m_MotionDirections.begin(), m_MotionDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i ActionTile = m_TilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

bool GAME_Character::TileIsInAttackDirections(baseplate::Vector2i tile) {

    if (std::any_of(m_AttackDirections.begin(), m_AttackDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i ActionTile = m_TilePosition + A;
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

void GAME_Character::MoveTo(baseplate::Vector2i tile_position) {

    GAME_Arena* Arena = GetParent<GAME_Arena>();

    if (Arena->CanMoveTo(tile_position) && tile_position != m_TilePosition) {

        m_TilePosition = tile_position;
        SetPosition(baseplate::Vector2(tile_position.X + tile_position.Y, tile_position.Y - tile_position.X) * Arena->GetTileSize());
    }

    m_Actions--;
}

void GAME_Character::AttackOn(baseplate::Vector2i tile_position) {

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

    mDisplayManager = &baseplate::Manager<GAME_DisplayManager>::Get();

    BuildCharacter();
    MoveTo(m_SpawnPosition);
}

void GAME_Character::_Draw() {

    mShaderAsset->Bind();

    GAME_Camera* CurrentCamera = GAME_Camera::CurrentCamera;
    baseplate::Vector2 TextureSize = mTextureAsset->TextureSize.ToVector2();

    baseplate::Vector2 CharacterPosition(GetPosition().X - TextureSize.X / 2, GetPosition().Y - TextureSize.Y);
    baseplate::Vector2 CharacterSize(TextureSize.X, TextureSize.Y);

    CurrentCamera->TransformToCameraView(CharacterPosition, CharacterSize);

    baseplate::base_glm::RenderModel Model(CharacterPosition, CharacterSize);
    Model.Bind(mShaderAsset->Program, "uModel");

    GLint ProjectionLoc = glGetUniformLocation(mShaderAsset->Program, "uProjection");
    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(mDisplayManager->GetProjection()));

    //nesse contexto é inultil, mas manti para uma futura implementação
    baseplate::Color4f BackgroundColorNormalized = BackgroundColor.Normalize();
    GLint BackgroundColorLoc = glGetUniformLocation(mShaderAsset->Program, "uBackgroundColor");
    glUniform4f(BackgroundColorLoc, BackgroundColorNormalized.R, BackgroundColorNormalized.G, BackgroundColorNormalized.B, BackgroundColorNormalized.A);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureAsset->Texture);

    GLint TextureLoc = glGetUniformLocation(mShaderAsset->Program, "uTexture");
    glUniform1i(TextureLoc, 0);

    glBindVertexArray(mDisplayManager->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}