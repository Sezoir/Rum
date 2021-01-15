#pragma once
// Std libs
#include <memory>
// Project files
#include "Renderer.hpp"

namespace Rum::Renderer
{
    class DrawContext
    {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual void setSwapInterval(uint8_t interval) = 0;

        static std::unique_ptr<DrawContext> create(void* window);
    };
} // namespace Rum::Renderer
