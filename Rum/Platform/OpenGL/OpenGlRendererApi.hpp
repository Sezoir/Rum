#pragma once
// Project files
#include "Renderer/RendererApi.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLRendererAPI : public Renderer::RendererAPI
    {
    public:
        void init() override;
        void setViewport() override;
        void setClearColour(const glm::vec4& colour) override;
        void clear() override;

        Renderer::DrawAPI getAPI() const override;
    };
} // namespace Rum::Platform::OpenGL
