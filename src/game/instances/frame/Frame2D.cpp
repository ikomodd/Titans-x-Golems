#include "Frame2D.hpp"

#include "game/managers/display/Display.hpp"

game::Frame2D::Frame2D(std::string name, baseplate::Vector2 position, baseplate::Vector2 size, baseplate::Vector2 anchor) : Node(name) {

    baseplate::Vector2 windowSize = baseplate::Manager<DisplayManager>::Get().GetWindowSize();

    positionAnchor = anchor;
    localPosition = position;
    localSize = size;

    UpdateTransform(windowSize);
}

//

void game::Frame2D::Ready() {

    DefineShaderAsset("color_shader");
    backgroundColor = baseplate::Color4(baseplate::ColorPressets::WHITE);
}

void game::Frame2D::Draw(GLuint vao, glm::mat4 projection) {

    glUseProgram(m_shaderAsset->program);

    baseplate::Color4f normalizedColor = backgroundColor.Normalize();
    GLint colorLoc = glGetUniformLocation(m_shaderAsset->program, "uColor");
    glUniform4f(colorLoc, normalizedColor.R, normalizedColor.G, normalizedColor.B, normalizedColor.A);

    baseplate::gl::RenderModel model(GetPosition(), GetSize());

    GLint modelLoc = glGetUniformLocation(m_shaderAsset->program, "uModel");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model.GetMatrix()));

    GLint projectionLoc = glGetUniformLocation(m_shaderAsset->program, "uProjection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}