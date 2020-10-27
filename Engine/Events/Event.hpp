#pragma once
// Std libs
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

namespace Engine::Events
{
#define EVENT_FN(fn) [&](Event& event) { fn(event); }
#define BIT(x)       1u << unsigned(x)

#define EVENT_CLASS_TYPE(type)                                                                                         \
    virtual EventType GetEventType() const override                                                                    \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual const char* GetName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CATEGORY_TYPE(category)                                                                                  \
    virtual EventCategory getEventCategory() const override                                                            \
    {                                                                                                                  \
        return category;                                                                                               \
    }

    enum class EventType
    {
        None,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved
    };

    // We use bit macro in-case we want to use bitwise operations later
    enum class EventCategory : uint32_t
    {
        None = 0,
        Window = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2)

    };
    EventCategory operator|(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(static_cast<std::underlying_type<EventCategory>::type>(lhs) |
                                          static_cast<std::underlying_type<EventCategory>::type>(rhs));
    }
    EventCategory operator&(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(static_cast<std::underlying_type<EventCategory>::type>(lhs) &
                                          static_cast<std::underlying_type<EventCategory>::type>(rhs));
    }

    class Event
    {
    public:
        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual EventCategory getEventCategory() const = 0;
        [[nodiscard]] virtual std::string ToString() const
        {
            return GetName();
        }

        template <typename T>
        T& convert()
        {
            if(T* cast = dynamic_cast<T*>(this))
            {
                return *cast;
            }
            else
            {
                // Error logging @todo
                std::cout << "Error: convert function for event " << GetName() << " failed to cast correctly"
                          << std::endl;
                exit(-1);
            }
        }
    };

    class Observer
    {
    public:
        void addSubject(std::function<void(Event&)> callback)
        {
            mSubjects.push_back(std::move(callback));
        }

        void notify(Event& event)
        {
            for(auto& x : mSubjects)
            {
                x(event);
            }
        }

    private:
        std::vector<std::function<void(Event&)>> mSubjects = {};
    };

} // namespace Engine::Events
