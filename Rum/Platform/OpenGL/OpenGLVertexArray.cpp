#include "OpenGLVertexArray.hpp"
// External libs
#include <glad/glad.h>
// Project files
#include "OpenGLUtilities.hpp"

namespace Rum::Platform::OpenGL
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &mBufferID);
    }

    OpenGLVertexArray::OpenGLVertexArray(size_t preAllocate)
    {
        glGenVertexArrays(1, &mBufferID);
        mVertexBuffers.reserve(preAllocate);
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(mBufferID);
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexObject(std::shared_ptr<Renderer::VertexBuffer> vbo)
    {
        // Bind VAO/VBO
        OpenGLVertexArray::bind();
        vbo->bind();

        // Setup properties
        const Renderer::ElementLayout& layout = vbo->getLayout();
        for(auto element : layout.getElements())
        {
            glVertexAttribPointer(mVertexObjectCount, element.getComponentCount(), getGLShaderType(element.mType),
                                  element.mNormalise, layout.getStride(), (void*) element.mOffset);
            glEnableVertexAttribArray(mVertexObjectCount);

            mVertexObjectCount++;
        }
        // Unbind vbo and store
        vbo->unbind();
        mVertexBuffers.push_back(std::move(vbo));
    }

    void OpenGLVertexArray::setIndexBuffer(std::unique_ptr<Renderer::IndexBuffer> ebo)
    {
        mIndexBuffer = std::move(ebo);
    }

    const Renderer::VertexBuffer& OpenGLVertexArray::getVertexBuffer(uint32_t index) const
    {
        return *mVertexBuffers[index];
    }

    const std::vector<std::shared_ptr<Renderer::VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
    {
        return mVertexBuffers;
    }

    const std::unique_ptr<Renderer::IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
    {
        return mIndexBuffer;
    }

} // namespace Rum::Platform::OpenGL