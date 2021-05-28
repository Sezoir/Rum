#include "OpenGLRendererApi.hpp"
// External libs
#include <glad/glad.h>

namespace Rum::Platform::OpenGL
{
    void OpenGLRendererAPI::init()
    {
    }

    void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::setClearColour(const glm::vec4& colour)
    {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    void OpenGLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Renderer::DrawAPI OpenGLRendererAPI::getAPI() const
    {
        return Renderer::DrawAPI::OpenGL;
    }
    void OpenGLRendererAPI::drawIndexed(const std::unique_ptr<Renderer::VertexArray>& vertexArray, uint32_t count)
    {
        const uint32_t indexCount = count == 0 ? vertexArray->getIndexBuffer()->getCount() : count;
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
} // namespace Rum::Platform::OpenGL
