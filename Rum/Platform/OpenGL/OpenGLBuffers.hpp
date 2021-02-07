#pragma once
// External libs
#include <glad/glad.h>
// Project files
#include "Renderer/Buffers.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLVertexBuffer : public Renderer::VertexBuffer
    {
    public:
        OpenGLVertexBuffer(size_t size);
        OpenGLVertexBuffer(float& vertices, Renderer::BufferMemoryType memoryType);

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
        OpenGLIndexBuffer(uint64_t& indices, Renderer::BufferMemoryType memoryType);
        ~OpenGLIndexBuffer();

        void bind() override;
        void unbind() override;
        void setData(uint64_t& indices);

    private:
        GLuint mBufferID = 0;
    };
} // namespace Rum::Platform::OpenGL
