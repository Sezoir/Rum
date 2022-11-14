#pragma once
#include "Scene/RObject.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include <glm/glm.hpp>

namespace Rum::Renderer::Objects
{
    class Cube : public Scene::RObject
    {
    public:
        Cube(Scene::Scene& scene, glm::vec3 position, glm::vec3 size, glm::vec3 rotation, glm::vec4 colour);
        ~Cube() = default;

    private:
        std::unique_ptr<Scene::Entity> mEntity;

        // @TODO: Should be replaced in the future with shader creator
        inline constexpr static std::string_view mVertShaderCode =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec2 aTexCoord;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "out vec2 TexCoord;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
            "    //    gl_Position = model * vec4(aPos, 1.0);\n"
            "    //    gl_Position = vec4(aPos, 1.0);\n"
            "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
            "}";

        inline constexpr static std::string_view const mFragShaderCode =
            "#version 330 core\n"
            "in vec2 TexCoord;\n"
            "out vec4 FragColor;\n"
            "uniform sampler2D texture1;\n"
            "void main()\n"
            "{\n"
            "    FragColor = texture(texture1, TexCoord);\n"
            "}";
    };
} // namespace Rum::Renderer::Objects
