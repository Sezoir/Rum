#pragma once
// Std libs
#include <memory>
// Project files
#include "Renderer.hpp"
#include "Core/Log.hpp"

namespace Rum::Renderer
{
    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() = default;

        virtual void setData(void* buffer) = 0;
        static std::shared_ptr<UniformBuffer> create(size_t size);
        static std::shared_ptr<UniformBuffer> create(void* buffer);

    protected:
        UniformBuffer() = default;
    };
} // namespace Rum::Renderer
