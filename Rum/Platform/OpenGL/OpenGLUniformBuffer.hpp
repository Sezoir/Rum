#pragma once
// External dependencies
#include <glad/glad.h>
// Project files
#include "Renderer/UniformBuffer.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLUniformBuffer : public Renderer::UniformBuffer
    {
    public:
        OpenGLUniformBuffer(void* buffer)
        {
            glGenBuffers(1, &mID);
            glBindBuffer(GL_UNIFORM_BUFFER, mID);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
            glBindBufferRange(GL_UNIFORM_BUFFER, 0, mID, 0, sizeof(buffer));
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        OpenGLUniformBuffer(size_t size)
        {
            glGenBuffers(1, &mID);
            glBindBuffer(GL_UNIFORM_BUFFER, mID);
            glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
            glBindBufferRange(GL_UNIFORM_BUFFER, 0, mID, 0, size);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void setData(void* buffer) override
        {
            glBindBuffer(GL_UNIFORM_BUFFER, mID);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(buffer), buffer);
        }

    private:
        GLuint mID;
    };
} // namespace Rum::Platform::OpenGL