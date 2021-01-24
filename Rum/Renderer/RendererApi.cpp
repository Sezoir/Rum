#include "RendererApi.hpp"
#include "Platform/OpenGL/OpenGLRendererApi.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<RendererAPI> RendererAPI::create(DrawAPI drawApi)
    {
        switch(drawApi)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Rum::Platform::OpenGL::OpenGLRendererAPI>();
            default:
            {
                RUM_CORE_ERROR("DrawAPI not supported");
                return nullptr;
            }
        }
    }
} // namespace Rum::Renderer
