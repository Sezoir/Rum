#include "OpenGLBuffers.hpp"

namespace Rum::Platform::OpenGL
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
    {
        glGenBuffers(1, &mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float& vertices, uint64_t memoryType = GL_STATIC_DRAW)
    {
        glGenBuffers(1, &mBufferID);
        bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, memoryType);
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

} // namespace Rum::Platform::OpenGL