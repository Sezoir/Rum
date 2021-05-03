#pragma once

// External libs
#include <glad/glad.h>
// Project files
#include "Renderer/Buffers.hpp"
#include "Renderer/Shader.hpp"

namespace Rum::Platform::OpenGL
{
    const GLenum getGLShaderType(Rum::Renderer::ShaderDataType type);

    const GLenum getGLMemoryType(Renderer::BufferMemoryType type);

    const std::string getShaderTypeName(Renderer::Shader::ShaderType type);

    const GLenum getGLShaderType(Renderer::Shader::ShaderType type);

    const std::string getCompilationStage(Renderer::Shader::CompilationStage stage);

    const GLenum getGLCompilationType(Renderer::Shader::CompilationStage stage);

} // namespace Rum::Platform::OpenGL