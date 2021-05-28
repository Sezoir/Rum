#include "Renderer.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<RendererAPI> Renderer::mRendererAPI = nullptr;

    void Renderer::init()
    {
        mRendererAPI = RendererAPI::create(DrawAPI::OpenGL);
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

} // namespace Rum::Renderer