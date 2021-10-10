#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace Rum::Renderer
{
    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual uint32_t getWidth() = 0;
        virtual uint32_t getHeight() = 0;

        virtual void setTexture(void* texture) = 0;

        virtual void bind(uint32_t units = 0) = 0;
        virtual void unbind() = 0;

    private:
    };

    class Texture2D : public Texture
    {
    public:
        static std::unique_ptr<Texture2D> create(uint32_t width, uint32_t height);
        static std::unique_ptr<Texture2D> create(std::string path);
    };
} // namespace Rum::Renderer
