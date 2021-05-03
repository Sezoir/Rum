#include "OpenGLUtilities.hpp"
// Project files
#include "Core/Log.hpp"

namespace Rum::Platform::OpenGL
{
    const GLenum getGLShaderType(Rum::Renderer::ShaderDataType type)
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

    const GLenum getGLMemoryType(Renderer::BufferMemoryType type)
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

    const std::string getShaderTypeName(Renderer::Shader::ShaderType type)
    {
        switch(type)
        {
            case Renderer::Shader::ShaderType::Vertex:
                return "Vertex";
            case Renderer::Shader::ShaderType::Fragment:
                return "Frag";
            case Renderer::Shader::ShaderType::Program:
                return "Program";
            default:
            {
                RUM_CORE_CRITICAL("Error: Unknown ShaderType with ID: {}. This should not occur.",
                                  static_cast<int>(type));
                return "Unknown Type";
            }
        }
    }

    const GLenum getGLShaderType(Renderer::Shader::ShaderType type)
    {
        // Returns the shader type. Note not all the enum types in ShaderType have a value corresponding with it
        // such as the ShaderType::Program.
        switch(type)
        {
            case Renderer::Shader::ShaderType::Vertex:
                return GL_VERTEX_SHADER;
            case Renderer::Shader::ShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
            default:
            {
                RUM_CORE_CRITICAL("Error: Failed to get shader type which is required. Did you use a non-valid\n"
                                  "ShaderType such as ShaderType::Program?");
                return 0;
            }
        }
    }

    const std::string getCompilationStage(Renderer::Shader::CompilationStage stage)
    {
        switch(stage)
        {
            case Renderer::Shader::CompilationStage::Compile:
                return "Compile";
            case Renderer::Shader::CompilationStage::Linking:
                return "Linking";
            default:
            {
                RUM_CORE_CRITICAL("Error: Unknown CompilationStage with ID: {}. This should not occur.",
                                  static_cast<int>(stage));
                return "Unknown Type";
            }
        }
    }

    const GLenum getGLCompilationType(Renderer::Shader::CompilationStage stage)
    {
        switch(stage)
        {
            case Renderer::Shader::CompilationStage::Compile:
                return GL_COMPILE_STATUS;
            case Renderer::Shader::CompilationStage::Linking:
                return GL_LINK_STATUS;
            default:
            {
                RUM_CORE_CRITICAL("Error: Unknown CompilationStage with ID: {}. This should not occur.",
                                  static_cast<int>(stage));
                return 0;
            }
        }
    }

} // namespace Rum::Platform::OpenGL