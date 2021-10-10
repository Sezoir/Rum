#include "Texture.hpp"

// Project files
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture2D.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLTexture2D>(width, height);
            default:
            {
                RUM_CORE_ERROR("No platform shader found for selected drawAPI.");
                return nullptr;
            }
        }
    }

    std::unique_ptr<Texture2D> Texture2D::create(std::string path)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLTexture2D>(path);
            default:
            {
                RUM_CORE_ERROR("No platform shader found for selected drawAPI.");
                return nullptr;
            }
        }
    }
} // namespace Rum::Renderer