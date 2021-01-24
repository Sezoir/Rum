#pragma once
#include "Renderer/Buffers.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLVertexBuffer : public Renderer::VertexBuffer
    {
    public:
        OpenGLVertexBuffer() = default;
        ~OpenGLVertexBuffer() = default;

        void bind() override;
        void unbind() override;

    private:
    };
} // namespace Rum::Platform::OpenGL
