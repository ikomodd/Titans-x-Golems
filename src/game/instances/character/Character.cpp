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

    if (std::any_of(mMotionDirections.begin(), mMotionDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i ActionTile = mTilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

bool game::Character::TileIsInAttackDirections(baseplate::Vector2i tile) {

    if (std::any_of(mAttackDirections.begin(), mAttackDirections.end(),
    [this, tile](const baseplate::Vector2i& A) {

        baseplate::Vector2i ActionTile = mTilePosition + A;
        return ActionTile.X == tile.X && ActionTile.Y == tile.Y;
    }))
        return true;
    return false;
}

void game::Character::BuildCharacter() {

    std::ifstream File("../" + mSourcePath);
    if (!File.is_open()) {
        std::cerr << "[game::Character] Erro ao abrir o arquivo: " << mSourcePath << "\n";
        return;
    }

    nlohmann::json Data = nlohmann::json::parse(File);

    Name = Data["id"];

    mHealth          = Data["health"];
    mShield          = Data["shield"];
    mDamage          = Data["damage"];
    mActionsQuantity = Data["actions"];

    mActions = mActionsQuantity + 1; // + 1 porque tem que conciderar o MoveTo quando o character é criado

    std::string TextureName = (Data["texture_name"] != "") ? Data["texture_name"] : "character_standart";
    DefineTextureAsset(TextureName);
    DefineShaderAsset("texture_shader");

    for (auto& [key, value] : Data["motion_directions"].items()) {

        mMotionDirections.emplace_back(value[0], value[1]);
    }

    for (auto& [key, value] : Data["attack_directions"].items()) {

        mAttackDirections.emplace_back(value[0], value[1]);
    }
}

void game::Character::MoveTo(baseplate::Vector2i tile_position) {

    Arena* arena = GetParent<Arena>();

    if (arena->CanMoveTo(tile_position) && tile_position != mTilePosition) {

        mTilePosition = tile_position;
        SetPosition(baseplate::Vector2(tile_position.X + tile_position.Y, tile_position.Y - tile_position.X) * arena->GetTileSize());
    }

    mActions--;
}

void game::Character::AttackOn(baseplate::Vector2i tile_position) {

    Arena* arena = GetParent<Arena>();

    arena->AttackTile(tile_position, mDamage);

    mActions--;
}

void game::Character::GetDamage(float damage) {

    float CurrentDamage = damage - mShield;
    if (CurrentDamage < 0) CurrentDamage = 0;
    if (mShield > 0) mShield--;

    mHealth -= CurrentDamage;

    std::cout << "Character: " << Name << " foi atacado; Health: " << mHealth << " Shield: " << mShield << "\n";

    if (mHealth <= 0)
        Destroy();
}

//

void game::Character::_Ready() {

    mDisplayManager = &baseplate::Manager<game::DisplayManager>::Get();

    BuildCharacter();
    MoveTo(mSpawnPosition);
}

void game::Character::_Draw(GLuint vao, glm::mat4 projection) {

    mShaderAsset->Bind();

    game::Camera* CurrentCamera = game::Camera::CurrentCamera;
    baseplate::Vector2 TextureSize = mTextureAsset->TextureSize.ToVector2();

    baseplate::Vector2 CharacterPosition(GetPosition().X - TextureSize.X / 2, GetPosition().Y - TextureSize.Y);
    baseplate::Vector2 CharacterSize(TextureSize.X, TextureSize.Y);

    CurrentCamera->TransformToCameraView(CharacterPosition, CharacterSize);

    baseplate::base_glm::RenderModel Model(CharacterPosition, CharacterSize);
    Model.Bind(mShaderAsset->Program, "uModel");

    GLint ProjectionLoc = glGetUniformLocation(mShaderAsset->Program, "uProjection");
    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //nesse contexto é inultil, mas manti para uma futura implementação
    baseplate::Color4f BackgroundColorNormalized = BackgroundColor.Normalize();
    GLint BackgroundColorLoc = glGetUniformLocation(mShaderAsset->Program, "uBackgroundColor");
    glUniform4f(BackgroundColorLoc, BackgroundColorNormalized.R, BackgroundColorNormalized.G, BackgroundColorNormalized.B, BackgroundColorNormalized.A);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureAsset->Texture);

    GLint TextureLoc = glGetUniformLocation(mShaderAsset->Program, "uTexture");
    glUniform1i(TextureLoc, 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}