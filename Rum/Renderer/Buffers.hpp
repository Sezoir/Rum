#pragma once
// Std libs
#include <memory>
#include <vector>
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

    enum class BufferMemoryType : uint64_t
    {
        STREAM_DRAW,
        STATIC_DRAW,
        DYNAMIC_DRAW
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
        ShaderDataType mType;
        std::string mName;
        uint32_t mSize = 0;
        size_t mOffset = 0;
        bool mNormalise = false;

        Element(ShaderDataType type, const std::string& name, bool normalise = false)
            : mType(type)
            , mName(name)
            , mSize(getShaderDataTypeSize(type))
            , mOffset(0)
            , mNormalise(normalise)
        {
        }

        Element(ShaderDataType type, uint32_t size, size_t offset, bool normalise = false)
            : mType(type)
            , mName("")
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

        const std::vector<Element>& getElements() const
        {
            return mElements;
        }

        uint32_t getStride() const
        {
            return mStride;
        }

        uint32_t getBufferSize() const
        {
            return mBufferSize;
        }

    private:
        void calculateOffsets()
        {
            size_t offset = 0;
            mStride = 0;
            mBufferSize = 0;
            for(auto& element : mElements)
            {
                element.mOffset = offset;
                offset += element.mSize;
                mStride += element.mSize;
                mBufferSize += getShaderDataTypeSize(element.mType) * element.mSize;
            }
        }

        uint32_t mStride = 0;
        uint32_t mBufferSize = 0;
        std::vector<Element> mElements;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void setData(float&) = 0;

        void setLayout(ElementLayout& layout)
        {
            mLayout = layout;
        }

        const ElementLayout& getLayout() const
        {
            return mLayout;
        }

        static std::shared_ptr<VertexBuffer> create(size_t size);
        static std::shared_ptr<VertexBuffer> create(float* vertices, size_t size,
                                                    BufferMemoryType memoryType = BufferMemoryType::STATIC_DRAW);

    protected:
        ElementLayout mLayout;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual uint32_t getCount() const = 0;

        static std::unique_ptr<IndexBuffer> create(uint32_t* indices, uint32_t count,
                                                   BufferMemoryType memoryType = BufferMemoryType::STATIC_DRAW);
    };
} // namespace Rum::Renderer
