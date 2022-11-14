#pragma once
#include "RendererBase.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Scene/RObject.hpp"
#include "Scene/Scene.hpp"
#include "Objects/Cube.hpp"
#include <glm/glm.hpp>

namespace Rum::Renderer
{
    class Renderer3D : public RendererBase
    {
    public:
        enum Primitive : uint32_t
        {
            Cube = 0,
            Sphere = 1
        };

        Renderer3D() = default;
        ~Renderer3D() = default;

        void init() override;

        template <Primitive shape>
        std::shared_ptr<Scene::RObject> drawPrimitive(Scene::Scene& scene, glm::vec3 position, glm::vec3 size,
                                                      glm::vec3 rotation, glm::vec4 colour)
        {
            switch(shape)
            {
                case Cube:
                    return createCube(scene, position, size, rotation, colour);
            }
        }

        std::shared_ptr<Objects::Cube> createCube(Scene::Scene& scene, glm::vec3 position, glm::vec3 size,
                                                  glm::vec3 rotation, glm::vec4 colour);

        // @TODO: drawSphere, drawModel

    private:
    };
} // namespace Rum::Renderer