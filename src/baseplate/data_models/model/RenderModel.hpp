#pragma once

#include "../vector/Vector2.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace baseplate::base_glm {

    struct RenderModel {
    private:

        ::glm::mat4 model = ::glm::mat4(1.0f);

    public:

        RenderModel(baseplate::Vector2 position, baseplate::Vector2 size) {

            model = glm::translate(model, glm::vec3(position.X, position.Y, 0.0f));
            model = glm::scale(model, glm::vec3(size.X, size.Y, 1.0f));
        }

        void Bind(GLuint program, std::string uniform_name = "uModel") {

            GLint uniformLocation = glGetUniformLocation(program, uniform_name.c_str());
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));
        }
    };
}