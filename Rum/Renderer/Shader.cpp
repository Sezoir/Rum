#include "Shader.hpp"

// Project files
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGlShader.hpp"
#include "Core/Log.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<Shader> Shader::create(std::string name, std::string vertexPath, std::string fragPath)
    {
        const DrawAPI api = Renderer::getDrawAPI();
        switch(api)
        {
            case DrawAPI::OpenGL:
                return std::make_unique<Platform::OpenGL::OpenGLShader>(name, vertexPath, fragPath);
            default:
            {
                RUM_CORE_ERROR("No platform shader found for selected drawAPI.");
                return nullptr;
            }
        }
    }
} // namespace Rum::Renderer