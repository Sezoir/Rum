#include "Renderer.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<RendererAPI> Renderer::mRendererAPI = nullptr;
    std::unique_ptr<Renderer3D> Renderer::mRenderer3D = nullptr;
    std::unique_ptr<ShaderManager> Renderer::mShaderManager = nullptr;

    void Renderer::init()
    {
        mRendererAPI = RendererAPI::create(DrawAPI::OpenGL);
        mRenderer3D = std::make_unique<Renderer3D>();
        mShaderManager = std::make_unique<ShaderManager>();

        mRenderer3D->init();
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

    const std::unique_ptr<Renderer3D>& Renderer::r3D()
    {
        return mRenderer3D;
    }

    const std::unique_ptr<ShaderManager>& Renderer::getShaderManager()
    {
        return mShaderManager;
    }
} // namespace Rum::Renderer