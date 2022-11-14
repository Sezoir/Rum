#pragma once
#include <glm/glm.hpp>
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"

namespace Rum
{
    struct TransformationComponent
    {
        glm::vec3 translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
    };

    struct MeshComponent
    {
        size_t shaderID;
        size_t vertexArrayID;
    };
} // namespace Rum