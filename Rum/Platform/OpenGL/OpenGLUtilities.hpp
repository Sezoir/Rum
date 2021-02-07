#pragma once
// External libs
#include <glad/glad.h>
// Project files
#include "Renderer/Buffers.hpp"

namespace Rum::Platform::OpenGL
{

    constexpr inline GLenum getGLShaderType(Rum::Renderer::ShaderDataType type)
    {
        using namespace Rum::Renderer;
        switch(type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
            {
                RUM_CORE_ERROR("ShaderDataType is not supported by OpenGL implementation.");
                return 0;
            }
        }
    }

    constexpr GLenum getGLMemoryType(Renderer::BufferMemoryType type)
    {
        switch(type)
        {
            case Renderer::BufferMemoryType::STATIC_DRAW:
                return GL_STATIC_DRAW;
            case Renderer::BufferMemoryType::DYNAMIC_DRAW:
                return GL_DYNAMIC_DRAW;
            case Renderer::BufferMemoryType::STREAM_DRAW:
                return GL_STREAM_READ;
            default:
            {
                RUM_CORE_ERROR("BufferMemoryType is not supported by OpenGL implementation.");
                return 0;
            }
        }
    }

} // namespace Rum::Platform::OpenGL