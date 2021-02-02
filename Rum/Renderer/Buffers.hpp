#pragma once
// Std libs
#include <memory>
#include <vector>
// External libs
#include <glad/glad.h>
// Project files
#include "Core/Log.hpp"

namespace Rum::Renderer
{
    enum class ShaderDataType : uint64_t
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static constexpr size_t getShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Float2:
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Float3:
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Float4:
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 4;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                RUM_CORE_ERROR("ShaderDataType size is not supported");
                return 0;
        }
    }

    struct Element
    {
        Element(ShaderDataType type, uint32_t size, size_t offset, bool normalise = false)
            : mType(type)
            , mSize(size)
            , mOffset(offset)
            , mNormalise(normalise)
        {
        }

        size_t getComponentCount() const
        {
            switch(mType)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Int:
                case ShaderDataType::Bool:
                    return 1;
                case ShaderDataType::Float2:
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Float3:
                case ShaderDataType::Mat3:
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Float4:
                case ShaderDataType::Mat4:
                case ShaderDataType::Int4:
                    return 4;
                default:
                    RUM_CORE_ERROR("ShaderDataType not support");
                    return 0;
            }
        }

        ShaderDataType mType = ShaderDataType::None;
        uint32_t mSize = 0;
        size_t mOffset = 0;
        bool mNormalise = false;
    };

    class ElementLayout
    {
    public:
        ElementLayout() = default;

        ElementLayout(std::initializer_list<Element> list)
            : mElements(list)
        {
            calculateOffsets();
        }

        const std::vector<Element>& getElements()
        {
            return mElements;
        }

        uint32_t getSize() const
        {
            return mSize;
        }

        uint32_t getBufferSize() const
        {
            return mBufferSize;
        }

    private:
        void calculateOffsets()
        {
            size_t offset = 0;
            mSize = 0;
            mBufferSize = 0;
            for(auto& element : mElements)
            {
                element.mOffset = offset;
                offset += element.mSize;
                mSize += element.mSize;
                mBufferSize += getShaderDataTypeSize(element.mType) * element.mSize;
            }
        }

        uint32_t mSize = 0;
        uint32_t mBufferSize = 0;
        std::vector<Element> mElements;
    };

    class VertexBuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        void setLayout(ElementLayout& layout)
        {
            mLayout = layout;
        }
        const ElementLayout& getLayout() const
        {
            return mLayout;
        }
        std::unique_ptr<VertexBuffer> create(size_t size);
        std::unique_ptr<VertexBuffer> create(float& vertices, uint64_t memoryType);

    protected:
        ElementLayout mLayout;
    };

    class IndexBuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        std::unique_ptr<IndexBuffer> create(float& vertices, uint64_t memoryType);
    };
} // namespace Rum::Renderer
