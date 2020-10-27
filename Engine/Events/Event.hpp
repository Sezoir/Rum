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

#define EVENT_CATEGORY_TYPE(type)                                                                                      \
    virtual EventCategory getEventCategory() const override                                                            \
    {                                                                                                                  \
        return EventCategory::type;                                                                                    \
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
    enum class EventCategory
    {
        None = 0,
        EventCategoryWindow = BIT(0),
        EventCategoryInput = BIT(1)
    };

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
