// Std libs
#include <memory>
// Rum files
#include <Rum.hpp>
#include <Renderer/Shader.hpp>
#include <Platform/OpenGL/OpenGlShader.hpp>
// External libs
#include <catch.hpp>

using namespace Rum::Renderer;
using namespace Rum::Platform::OpenGL;

TEST_CASE("Testing compilation of shader", "[Renderer][Shader]")
{
    SECTION("From given string")
    {
        auto shader = Shader::create("test", "", "");
        REQUIRE(shader->getName() == "test");

        const std::string vertexCode = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                       "}\n";
        const std::string fragmentCode = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                         "}\n";

        shader->compile(vertexCode, fragmentCode);
        shader->bind();
        shader->unbind();
    }

    SECTION("From test files")
    {
        auto shader = Shader::create("test", "shader.vert", "shader.frag");
        REQUIRE(shader->getName() == "test");

        shader->compile();
        shader->bind();
        shader->unbind();
    }
}