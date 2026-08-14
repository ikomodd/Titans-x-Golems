#include "TextLabel.hpp"

#include "game/managers/display/Display.hpp"

#include <algorithm>

void game::TextLabel::ChangeText(std::string text) {

    RenderText(text, textColor);
    
    auto& displayManager = baseplate::Manager<DisplayManager>::Get();

    baseplate::Vector2 textureSize = m_textureAsset->textureSize.ToVector2();
    baseplate::Vector2 windowSize = displayManager.GetWindowSize();

    /*
    [TODO] Essa parte ta estranha, mas funciona. basicamente ele ta transformando em scale, mas dentro do
    UpdateTransform() ele faz o contrário, poderia tem um esquema para poder atualizar o size ou scale de
    forma separada.
    */
    int axis = std::max(windowSize.X, windowSize.Y);

    localSize = textureSize / axis;
    UpdateTransform(windowSize);
}

//

void game::TextLabel::Ready() {

    DefineShaderAsset("texture_shader");
}

void game::TextLabel::Draw(GLuint vao, glm::mat4 projection) {

    glUseProgram(m_shaderAsset->program);

    baseplate::gl::RenderModel model(GetPosition(), GetSize());

    GLint modelLoc = glGetUniformLocation(m_shaderAsset->program, "uModel");
    glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model.GetMatrix()));

    GLint projectionLoc = glGetUniformLocation(m_shaderAsset->program, "uProjection");
    glUniformMatrix4fv(projectionLoc, 1, false, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureAsset->texture);

    baseplate::Color4f normalizedColor = backgroundColor.Normalize();
    GLint backgroundColorLoc = glGetUniformLocation(m_shaderAsset->program, "uBackgroundColor");
    glUniform4f(backgroundColorLoc, normalizedColor.R, normalizedColor.G, normalizedColor.B, normalizedColor.A);

    GLint textureLoc = glGetUniformLocation(m_shaderAsset->program, "uTexture");
    glUniform1i(textureLoc, 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}