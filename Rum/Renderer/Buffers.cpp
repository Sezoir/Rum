#include "Buffers.hpp"
// Project files
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffers.hpp"

namespace Rum::Renderer
{
    std::shared_ptr<VertexBuffer> VertexBuffer::create(size_t size)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_shared<Platform::OpenGL::OpenGLVertexBuffer>(size);
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::create(float& vertices, BufferMemoryType memoryType)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_shared<Platform::OpenGL::OpenGLVertexBuffer>(vertices, memoryType);
            default:
                RUM_CORE_ERROR("VertexBuffer not supported for current draw API: %s", drawApiToString(api));
                return nullptr;
        }
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::create(uint64_t& indices, BufferMemoryType memoryType)
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