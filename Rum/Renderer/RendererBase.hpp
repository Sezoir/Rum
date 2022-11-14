#pragma once
#include "Camera.hpp"

namespace Rum::Renderer
{
    class RendererBase
    {
    public:
        virtual void init() = 0;

    protected:
        RendererBase() = default;
    };
} // namespace Rum::Renderer
