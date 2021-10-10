#pragma once
// Std libs
#include <string>

// External libs
#include <glad/glad.h>

// Project files
#include "Renderer/Texture.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLTexture2D : public Renderer::Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(std::string path);
        ~OpenGLTexture2D();

        uint32_t getWidth() override;
        uint32_t getHeight() override;
        void setTexture(void* texture) override;
        void bind(uint32_t units) override;
        void unbind() override;

    private:
        GLuint mBufferID = 0;
        uint32_t mWidth;
        uint32_t mHeight;
    };
} // namespace Rum::Platform::OpenGL
