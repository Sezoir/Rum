#include "Buffers.hpp"
#include "Core/Log.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffers.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<VertexBuffer> VertexBuffer::create(size_t size)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLVertexBuffer>(size);
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::create(float& vertices, uint64_t memoryType)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLVertexBuffer>(vertices, memoryType);
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::create(float& indices, uint64_t memoryType)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLIndexBuffer>(indices, memoryType);
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }
} // namespace Rum::Renderer