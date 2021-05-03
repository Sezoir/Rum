#pragma once
// External libs
#include <glad/glad.h>
// Project files
#include "Renderer/Shader.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLShader : public Renderer::Shader
    {
    public:
        OpenGLShader(const std::string& name, std::string& vertexPath, std::string& fragPath);
        ~OpenGLShader();

        const std::string& getName() override;
        void unbind() override;
        bool compile() override;
        bool compile(const std::string& vertexCode, const std::string& fragmentCode) override;
        void bind() override;

    private:
        const std::string mName;
        const std::string mVertexPath;
        const std::string mFragPath;
        GLuint mShaderID = 0;
        void createShaderProgram(const std::string& vertexCode, const std::string& fragCode);
        GLuint createShader(const std::string& shaderCode, ShaderType type);
        void checkForCompileErrors(GLuint id, CompilationStage compStage, ShaderType shaderType);
    };
} // namespace Rum::Platform::OpenGL
