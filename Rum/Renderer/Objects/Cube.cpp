#include "Cube.hpp"
#include "Core/Application.hpp"
#include "Scene/Components.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Renderer/VertexArray.hpp"

namespace Rum::Renderer::Objects
{
    Rum::Renderer::Objects::Cube::Cube(Scene::Scene& scene, glm::vec3 position, glm::vec3 size, glm::vec3 rotation,
                                       glm::vec4 colour)
        : mEntity(scene.createEntity())
    {
        mEntity->addComponent<TransformationComponent>(position, rotation);
        auto a = VertexArray::create();
    }
} // namespace Rum::Renderer::Objects
