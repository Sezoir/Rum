#include "DrawContext.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"
namespace Rum::Renderer
{
    std::unique_ptr<DrawContext> DrawContext::create(void* window)
    {
        switch(Renderer::Renderer::getDrawAPI())
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLContext>(static_cast<GLFWwindow*>(window));
            default:
            {
                RUM_CORE_ERROR("DrawAPI not supported");
                return nullptr;
            }
        }
    }
} // namespace Rum::Renderer
