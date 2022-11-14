#include "Renderer3D.hpp"

namespace Rum::Renderer
{
    void Renderer3D::init()
    {
    }

    std::shared_ptr<Objects::Cube> Renderer3D::createCube(Scene::Scene& scene, glm::vec3 position, glm::vec3 size,
                                                          glm::vec3 rotation, glm::vec4 colour)
    {
        return std::make_shared<Objects::Cube>(scene, position, size, rotation, colour);
    }
} // namespace Rum::Renderer