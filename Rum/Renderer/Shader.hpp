#pragma once
// Std libs
#include <memory>
#include <string>
// External libs
#include <glm/glm.hpp>
// Project files
#include "Texture.hpp"

namespace Rum::Renderer
{
    class Shader
    {
    public:
        enum class ShaderType
        {
            Vertex,
            Fragment,
            Program
        };
        enum class CompilationStage
        {
            Compile,
            Linking
        };

        Shader() = default;
        virtual ~Shader() = default;

        virtual const std::string& getName() = 0;
        // @TODO: Maybe return a reference to itself than bool to enable code like:
        // auto shader = Shader::create("triangle", "shader.vert", "shader.frag").compile();
        // Error handling should be done by the engine, that is with the Logging classes.
        virtual bool compile() = 0;
        virtual bool compile(const std::string& vertexCode, const std::string& fragmentCode) = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setBool(const std::string& name, const bool& value) = 0;
        virtual void setInt(const std::string& name, const int& value) = 0;
        virtual void setFloat(const std::string& name, const float& value) = 0;
        virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
        virtual void setTexture(const std::string& name, const std::shared_ptr<Rum::Renderer::Texture2D> value) = 0;

        static std::unique_ptr<Shader> create(std::string name, std::string vertexPath, std::string fragPath);

    private:
    };
} // namespace Rum::Renderer
