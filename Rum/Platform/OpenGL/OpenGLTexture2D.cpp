#include "OpenGLTexture2D.hpp"

// Std lib
#include <filesystem>

// External libs
#include <stb/stb_image.h>

// Project files
#include <Core/Assert.hpp>
#include <Core/Log.hpp>

namespace Rum::Platform::OpenGL
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : mWidth(width)
        , mHeight(height)
    {
        glGenTextures(1, &mBufferID);
        glTextureStorage2D(mBufferID, 1, GL_RGBA8, mWidth, mHeight);

        glBindTexture(GL_TEXTURE_2D, mBufferID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::OpenGLTexture2D(std::string path)
    {
        std::filesystem::path file = path;
        if(file.is_relative())
        {
            file = std::filesystem::canonical(file);
        }
        RUM_CORE_ASSERT(std::filesystem::exists(file), "Path to texture \"" + path + "\" does not exist.");

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data;
        data = stbi_load(file.string().c_str(), &width, &height, &channels, 0);
        RUM_CORE_ASSERT(data != nullptr, "Failed to load texture.");

        mWidth = width;
        mHeight = height;
        GLenum internalFormat = 0, sizedInternalFormat = 0;
        if(channels == 3)
        {
            internalFormat = GL_RGB;
            sizedInternalFormat = GL_RGB8;
        }
        else if(channels == 4)
        {
            internalFormat = GL_RGBA;
            sizedInternalFormat = GL_RGBA8;
        }
        RUM_CORE_ASSERT(internalFormat != 0 || sizedInternalFormat == 0, "Unsupported number of channels.");

        glGenTextures(1, &mBufferID);

        glBindTexture(GL_TEXTURE_2D, mBufferID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &mBufferID);
    }

    uint32_t OpenGLTexture2D::getWidth()
    {
        return mWidth;
    }

    uint32_t OpenGLTexture2D::getHeight()
    {
        return mHeight;
    }

    void OpenGLTexture2D::setTexture(void* texture)
    {
        glTextureSubImage2D(mBufferID, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    }

    void OpenGLTexture2D::bind(uint32_t units)
    {
        glBindTextureUnit(units, mBufferID);
    }

    void OpenGLTexture2D::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace Rum::Platform::OpenGL