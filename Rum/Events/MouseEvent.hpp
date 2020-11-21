#pragma once
// Std libs
#include <string>
#include <sstream>
// Project files
#include "Event.hpp"
#include "Core/MouseCodes.hpp"

namespace Rum::Events
{

    class MouseMoveEvent : public Event
    {
    public:
        explicit MouseMoveEvent(const double x, const double y)
            : mX(x)
            , mY(y)
        {
        }

        [[nodiscard]] double getX() const
        {
            return mX;
        };

        [[nodiscard]] double getY() const
        {
            return mY;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMoveEvent: "
               << "X = " << mX << ", Y = " << mY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CATEGORY_TYPE(EventCategory::Mouse | EventCategory::Input);

    private:
        const double mX, mY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        explicit MouseScrolledEvent(const double x, const double y)
            : mX(x)
            , mY(y)
        {
        }

        [[nodiscard]] double getXOffset() const
        {
            return mX;
        };

        [[nodiscard]] double getYOffset() const
        {
            return mY;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: "
               << "XOffset = " << mX << ", YOffset = " << mY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CATEGORY_TYPE(EventCategory::Mouse | EventCategory::Input);

    private:
        const double mX, mY;
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        explicit MouseButtonPressedEvent(const Core::Mouse::Button button)
            : mButton(button)
        {
        }

        [[nodiscard]] Core::Mouse::Button getButton() const
        {
            return mButton;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: "
               << "Button = " << static_cast<Core::Mouse::MouseCode>(mButton);
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
        EVENT_CATEGORY_TYPE(EventCategory::Mouse | EventCategory::Input);

    private:
        const Core::Mouse::Button mButton;
    };

    class MouseButtonReleasedEvent : public Event
    {
    public:
        explicit MouseButtonReleasedEvent(const Core::Mouse::Button button)
            : mButton(button)
        {
        }

        [[nodiscard]] Core::Mouse::Button getButton() const
        {
            return mButton;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: "
               << "Button = " << static_cast<Core::Mouse::MouseCode>(mButton);
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
        EVENT_CATEGORY_TYPE(EventCategory::Mouse | EventCategory::Input);

    private:
        const Core::Mouse::Button mButton;
    };

} // namespace Rum::Events