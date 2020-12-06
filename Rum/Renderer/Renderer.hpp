#pragma once
// Std libs
#include <memory>
// Project files
#include "RendererApi.hpp"

namespace Rum::Renderer
{
    class Renderer
    {
    public:
        static void init();
        static void setDrawAPI(const DrawAPI& drawAPI);
        static const DrawAPI getDrawAPI();

    private:
        static std::unique_ptr<RendererAPI> mRendererAPI;
    };
} // namespace Rum::Renderer
