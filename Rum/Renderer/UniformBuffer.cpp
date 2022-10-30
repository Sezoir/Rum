#include "UniformBuffer.hpp"

#include "Platform/OpenGL/OpenGLUniformBuffer.hpp"

namespace Rum::Renderer
{
    std::shared_ptr<UniformBuffer> UniformBuffer::create(size_t size)
    {
        switch(Renderer::getDrawAPI())
        {
            case DrawAPI::OpenGL:
            {
                return std::make_unique<Rum::Platform::OpenGL::OpenGLUniformBuffer>(size);
            }
            default:
            {
                RUM_CORE_ERROR("Draw API is not supported");
                return nullptr;
            }
        }
    }

    std::shared_ptr<UniformBuffer> UniformBuffer::create(void* buffer)
    {
        switch(Renderer::getDrawAPI())
        {
            case DrawAPI::OpenGL:
            {
                return std::make_unique<Rum::Platform::OpenGL::OpenGLUniformBuffer>(buffer);
            }
            default:
            {
                RUM_CORE_ERROR("Draw API is not supported");
                return nullptr;
            }
        }
    }

} // namespace Rum::Renderer