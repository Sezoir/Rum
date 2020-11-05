#pragma once
// Std libs
#include <string>
#include <sstream>
// External libs
#include <SFML/Window.hpp>
// Project files
#include "Event.hpp"

namespace Rum::Events
{
    class KeyPressedEvent : public Event
    {
    public:
        KeyPressedEvent(const sf::Event::KeyEvent key)
            : mKey(key)
        {
        }

        sf::Event::KeyEvent getKey() const
        {
            return mKey;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKey.code;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
        EVENT_CATEGORY_TYPE(EventCategory::Keyboard | EventCategory::Input);

    private:
        const sf::Event::KeyEvent mKey;
    };

    class KeyReleasedEvent : public Event
    {
    public:
        KeyReleasedEvent(const sf::Event::KeyEvent key)
            : mKey(key)
        {
        }

        sf::Event::KeyEvent getKey() const
        {
            return mKey;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << mKey.code;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
        EVENT_CATEGORY_TYPE(EventCategory::Keyboard | EventCategory::Input);

    private:
        const sf::Event::KeyEvent mKey;
    };

} // namespace Rum::Events