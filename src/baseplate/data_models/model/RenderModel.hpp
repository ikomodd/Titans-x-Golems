#pragma once

#include "../vector/Vector2.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace baseplate::gl {

    struct RenderModel {
    private:

        glm::mat4 m_model = ::glm::mat4(1.0f);

    public:

        RenderModel(baseplate::Vector2 position, baseplate::Vector2 size) {

            m_model = glm::translate(m_model, glm::vec3(position.X, position.Y, 0.0f));
            m_model = glm::scale(m_model, glm::vec3(size.X, size.Y, 1.0f));
        }

        glm::mat4 GetMatrix() {

            return m_model;
        }
    };
}