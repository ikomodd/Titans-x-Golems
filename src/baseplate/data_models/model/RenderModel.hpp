#pragma once

#include "../vector/Vector2.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace baseplate::base_glm {

    struct RenderModel {
    private:

        glm::mat4 Model = glm::mat4(1.0f);

    public:

        RenderModel(baseplate::Vector2 position, baseplate::Vector2 size) {

            Model = glm::translate(Model, glm::vec3(position.X, position.Y, 0.0f));
            Model = glm::scale(Model, glm::vec3(size.X, size.Y, 1.0f));
        }

        void Bind(GLuint program, const char* uniform_name = "uModel") {

            GLint UniformLocation = glGetUniformLocation(program, uniform_name);
            glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, glm::value_ptr(Model));
        }
    };
}