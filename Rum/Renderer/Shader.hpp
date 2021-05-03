#pragma once
// Std libs
#include <memory>
#include <string>

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

        virtual ~Shader() = default;

        virtual const std::string& getName() = 0;
        virtual bool compile() = 0;
        virtual bool compile(const std::string& vertexCode, const std::string& fragmentCode) = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        static std::unique_ptr<Shader> create(std::string name, std::string vertexPath, std::string fragPath);

    private:
    };
} // namespace Rum::Renderer
