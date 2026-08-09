#include "TextureLabel.hpp"

void game::TextureLabel::Ready() {

    DefineShaderAsset("texture_shader");
    DefineTextureAsset(m_textureName);
}

void game::TextureLabel::Draw(GLuint vao, glm::mat4 projection) {

    glUseProgram(m_shaderAsset->program);

    baseplate::gl::RenderModel model(GetPosition(), GetSize());

    GLint modelLoc = glGetUniformLocation(m_shaderAsset->program, "uModel");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model.GetMatrix()));

    GLint projectionLoc = glGetUniformLocation(m_shaderAsset->program, "uProjection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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