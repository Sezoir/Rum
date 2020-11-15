#pragma once
// Std libs
#include <string>
#include <sstream>
// External libs
#include <SFML/Window.hpp>
// Project files
#include "Event.hpp"
#include "Core/KeyCodes.hpp"

namespace Rum::Events
{
    struct KeyEvent
    {
        // From SFML KeyEvent
        Core::Keyboard::Key code = Core::Keyboard::Key::Unknown; //!< Code of the key that has been pressed
        bool alt = false;                                        //!< Is the Alt key pressed?
        bool control = false;                                    //!< Is the Control key pressed?
        bool shift = false;                                      //!< Is the Shift key pressed?
        bool system = false;                                     //!< Is the System key pressed?
    };

    class KeyPressedEvent : public Event
    {
    public:
        explicit KeyPressedEvent(const KeyEvent key)
            : mKey(key)
        {
        }

        [[nodiscard]] KeyEvent getKey() const
        {
            return mKey;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << static_cast<Core::Keyboard::KeyCode>(mKey.code);
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
        EVENT_CATEGORY_TYPE(EventCategory::Keyboard | EventCategory::Input);

    private:
        const KeyEvent mKey;
    };

    class KeyReleasedEvent : public Event
    {
    public:
        explicit KeyReleasedEvent(const KeyEvent key)
            : mKey(key)
        {
        }

        [[nodiscard]] KeyEvent getKey() const
        {
            return mKey;
        };

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << static_cast<Core::Keyboard::KeyCode>(mKey.code);
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
        EVENT_CATEGORY_TYPE(EventCategory::Keyboard | EventCategory::Input);

    private:
        const KeyEvent mKey;
    };

} // namespace Rum::Events