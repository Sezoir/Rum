#pragma once
#include "Renderer/Buffers.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLVertexBuffer : public Renderer::VertexBuffer
    {
    public:
        OpenGLVertexBuffer(size_t size);
        OpenGLVertexBuffer(float& vertices, uint64_t memoryType);
        ~OpenGLVertexBuffer();

        void bind() override;
        void unbind() override;
        void setData(float& vertices);

    private:
        GLuint mBufferID = 0;
    };

    class OpenGLIndexBuffer : public Renderer::IndexBuffer
    {
    public:
        OpenGLIndexBuffer(float& vertices, uint64_t memoryType);
        ~OpenGLIndexBuffer();

        void bind() override;
        void unbind() override;
        void setData(float& vertices);

    private:
        GLuint mBufferID = 0;
    };
} // namespace Rum::Platform::OpenGL
