#pragma once
// Std libs
#include <memory>
#include <string>
// External lib
#include <glm/glm.hpp>
// Project files
#include "Core/Log.hpp"

namespace Rum::Renderer
{
    enum class DrawAPI
    {
        None,
        OpenGL
    };

    constexpr std::string_view drawApiToString(const DrawAPI drawApi)
    {
        switch(drawApi)
        {
            case DrawAPI::OpenGL:
                return "OpenGL";
            default:
                return "None";
        }
    }

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;
        static std::unique_ptr<RendererAPI> create(DrawAPI drawApi);

        virtual void init() = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void setClearColour(const glm::vec4& colour) = 0;
        virtual void clear() = 0;

        virtual DrawAPI getAPI() const = 0;

    private:
    };
} // namespace Rum::Renderer
