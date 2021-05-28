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
        OpenGLVertexBuffer(float* vertices, size_t size, Renderer::BufferMemoryType memoryType);

        ~OpenGLVertexBuffer();

        void bind() override;
        void unbind() override;
        void setData(float& vertices) override;

    private:
        GLuint mBufferID = 0;
    };

    class OpenGLIndexBuffer : public Renderer::IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count, Renderer::BufferMemoryType memoryType);
        ~OpenGLIndexBuffer();

        void bind() override;
        void unbind() override;
        uint32_t getCount() const override;
        void setData(uint32_t& indices);

    private:
        GLuint mBufferID = 0;
        uint32_t mCount;
    };
} // namespace Rum::Platform::OpenGL
