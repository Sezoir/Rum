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

        void setBool(const std::string& name, const bool& value) override;
        void setInt(const std::string& name, const int& value) override;
        void setFloat(const std::string& name, const float& value) override;
        void setFloat2(const std::string& name, const glm::vec2& value) override;
        void setFloat3(const std::string& name, const glm::vec3& value) override;
        void setFloat4(const std::string& name, const glm::vec4& value) override;
        void setMat4(const std::string& name, const glm::mat4& value) override;

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
