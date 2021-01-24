#include "Buffers.hpp"
#include "Core/Log.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<VertexBuffer> VertexBuffer::create()
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLVertexBuffer>();
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }
} // namespace Rum::Renderer