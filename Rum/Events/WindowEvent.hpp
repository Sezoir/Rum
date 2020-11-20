#pragma once
// Std libs
#include <string>
#include <sstream>
#include <cstdint>
// Project files
#include "Event.hpp"

namespace Rum::Events
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
            : mWidth(width)
            , mHeight(height)
        {
        }

        [[nodiscard]] uint32_t getWidth() const
        {
            return mWidth;
        }
        [[nodiscard]] uint32_t getHeight() const
        {
            return mHeight;
        }

        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CATEGORY_TYPE(EventCategory::Window)
    private:
        const uint32_t mWidth, mHeight;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CATEGORY_TYPE(EventCategory::Window)
    };
} // namespace Rum::Events