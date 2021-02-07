#include "OpenGLBuffers.hpp"
// Project files
#include "OpenGLUtilities.hpp"

namespace Rum::Platform::OpenGL
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
    {
        glGenBuffers(1, &mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(
        float& vertices, Renderer::BufferMemoryType memoryType = Renderer::BufferMemoryType::STATIC_DRAW)
    {
        glGenBuffers(1, &mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, getGLMemoryType(memoryType));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &mBufferID);
    }

    void OpenGLVertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
    }

    void OpenGLVertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setData(float& vertices)
    {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint64_t& indices, Renderer::BufferMemoryType memoryType)
    {
        glGenBuffers(1, &mBufferID);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, getGLMemoryType(memoryType));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &mBufferID);
    }

    void OpenGLIndexBuffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
    }

    void OpenGLIndexBuffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
    }

    void OpenGLIndexBuffer::setData(uint64_t& indices)
    {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), &indices);
    }
} // namespace Rum::Platform::OpenGL