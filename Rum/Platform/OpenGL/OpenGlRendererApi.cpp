#include "OpenGlRendererApi.hpp"

namespace Rum::Platform::OpenGL
{
    void OpenGLRendererAPI::init()
    {
    }

    void OpenGLRendererAPI::setViewport()
    {
    }

    void OpenGLRendererAPI::setClearColour(const glm::vec4& colour)
    {
    }

    void OpenGLRendererAPI::clear()
    {
    }

    Renderer::DrawAPI OpenGLRendererAPI::getAPI() const
    {
        return Renderer::DrawAPI::OpenGl;
    }
} // namespace Rum::Platform::OpenGL
