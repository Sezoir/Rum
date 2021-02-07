#include "VertexArray.hpp"

// Project files
#include "Renderer.hpp"
#include "Core/Log.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<VertexArray> VertexArray::create()
    {
        switch(Renderer::getDrawAPI())
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLVertexArray>();
            default:
            {
                RUM_CORE_ERROR("Draw API is not supported");
                return nullptr;
            }
        }
    }
} // namespace Rum::Renderer