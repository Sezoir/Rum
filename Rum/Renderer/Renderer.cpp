#include "Renderer.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<RendererAPI> Renderer::mRendererAPI = nullptr;
    std::unique_ptr<ShaderManager> Renderer::mShaderManager = nullptr;

    void Renderer::init()
    {
        mRendererAPI = RendererAPI::create(DrawAPI::OpenGL);
        mShaderManager = std::make_unique<ShaderManager>();
    }

    void Renderer::setDrawAPI(const DrawAPI& drawAPI)
    {
        mRendererAPI = RendererAPI::create(drawAPI);
    }

    const DrawAPI Renderer::getDrawAPI()
    {
        return mRendererAPI->getAPI();
    }

    const std::unique_ptr<RendererAPI>& Renderer::getAPI()
    {
        return mRendererAPI;
    }

    const std::unique_ptr<ShaderManager>& Renderer::getShaderManager()
    {
        return mShaderManager;
    }
} // namespace Rum::Renderer