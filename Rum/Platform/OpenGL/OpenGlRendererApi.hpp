#pragma once
// Project files
#include "Renderer/RendererApi.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLRendererAPI : public Renderer::RendererAPI
    {
    public:
        void init() override;
        void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void setClearColour(const glm::vec4& colour) override;
        void clear() override;

        Renderer::DrawAPI getAPI() const override;
    };
} // namespace Rum::Platform::OpenGL
