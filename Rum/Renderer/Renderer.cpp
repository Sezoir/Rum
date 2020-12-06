#include "Renderer.hpp"

namespace Rum::Renderer
{
    std::unique_ptr<RendererAPI> Renderer::mRendererAPI = nullptr;

    void Renderer::init()
    {
        mRendererAPI = RendererAPI::create(DrawAPI::OpenGl);
    }

    void Renderer::setDrawAPI(const DrawAPI& drawAPI)
    {
        mRendererAPI = RendererAPI::create(drawAPI);
    }

    const DrawAPI Renderer::getDrawAPI()
    {
        return mRendererAPI->getAPI();
    }

} // namespace Rum::Renderer