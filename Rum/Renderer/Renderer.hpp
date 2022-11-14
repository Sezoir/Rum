#pragma once
// Std libs
#include <memory>
// Project files
#include "RendererApi.hpp"
#include "ShaderManager.hpp"

namespace Rum::Renderer
{
    class Renderer
    {
    public:
        static void init();
        static void setDrawAPI(const DrawAPI& drawAPI);
        static const DrawAPI getDrawAPI();
        static const std::unique_ptr<RendererAPI>& getAPI();
        static const std::unique_ptr<ShaderManager>& getShaderManager();

    private:
        static std::unique_ptr<RendererAPI> mRendererAPI;
        static std::unique_ptr<ShaderManager> mShaderManager;
    };
} // namespace Rum::Renderer
