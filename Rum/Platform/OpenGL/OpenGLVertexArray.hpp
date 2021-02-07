#pragma once
// Std libs
#include <vector>
#include <memory>
// Project files
#include "OpenGLBuffers.hpp"
#include "Renderer/Buffers.hpp"
#include "Renderer/VertexArray.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLVertexArray : public Renderer::VertexArray
    {
    public:
        OpenGLVertexArray();
        OpenGLVertexArray(size_t preAllocate);
        ~OpenGLVertexArray() = default;

        void bind() const override;
        void unbind() const override;
        void addVertexObject(std::shared_ptr<Renderer::VertexBuffer>& vbo) override;
        void setIndexBuffer(std::unique_ptr<Renderer::IndexBuffer>& ebo) override;

        const Renderer::VertexBuffer& getVertexBuffer(uint32_t index) const override;
        const std::vector<std::shared_ptr<Renderer::VertexBuffer>>& getVertexBuffers() const override;
        const Renderer::IndexBuffer& getIndexBuffer() const override;

    private:
        GLuint mBufferID = 0;
        uint64_t mVertexObjectCount = 0;
        std::vector<std::shared_ptr<Renderer::VertexBuffer>> mVertexBuffers;
        std::unique_ptr<Renderer::IndexBuffer> mIndexBuffer = nullptr;
    };
} // namespace Rum::Platform::OpenGL
