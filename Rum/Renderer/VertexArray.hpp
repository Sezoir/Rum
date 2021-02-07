#pragma once
// Std libs
#include <memory>
#include <vector>
// Project files
#include "Buffers.hpp"

namespace Rum::Renderer
{
    class VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void addVertexObject(std::shared_ptr<VertexBuffer>& vbo) = 0;
        virtual void setIndexBuffer(std::unique_ptr<IndexBuffer>& ebo) = 0;

        virtual const VertexBuffer& getVertexBuffer(uint32_t index) const = 0;
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const IndexBuffer& getIndexBuffer() const = 0;

        static std::unique_ptr<VertexArray> create();
    };
} // namespace Rum::Renderer
