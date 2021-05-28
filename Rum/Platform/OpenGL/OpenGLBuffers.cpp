#include "OpenGLBuffers.hpp"
// Project files
#include "OpenGLUtilities.hpp"

namespace Rum::Platform::OpenGL
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
    {
        glGenBuffers(1, &mBufferID);
        OpenGLVertexBuffer::bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(
        float* vertices, size_t size, Renderer::BufferMemoryType memoryType = Renderer::BufferMemoryType::STATIC_DRAW)
    {
        glGenBuffers(1, &mBufferID);
        OpenGLVertexBuffer::bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, getGLMemoryType(memoryType));
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

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count, Renderer::BufferMemoryType memoryType)
        : mCount(count)
    {
        glGenBuffers(1, &mBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, getGLMemoryType(memoryType));
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGLIndexBuffer::getCount() const
    {
        return mCount;
    }

    void OpenGLIndexBuffer::setData(uint32_t& indices)
    {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), &indices);
    }

} // namespace Rum::Platform::OpenGL