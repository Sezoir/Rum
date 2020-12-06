#pragma once
// Std libs
#include <memory>
// External lib
#include <glm/glm.hpp>
// Project files
#include "Core/Log.hpp"

namespace Rum::Renderer
{
    enum class DrawAPI
    {
        None,
        OpenGl
    };

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;
        static std::unique_ptr<RendererAPI> create(DrawAPI drawApi);

        virtual void init() = 0;
        virtual void setViewport() = 0;
        virtual void setClearColour(const glm::vec4& colour) = 0;
        virtual void clear() = 0;

        virtual DrawAPI getAPI() const = 0;

    private:
    };
} // namespace Rum::Renderer
