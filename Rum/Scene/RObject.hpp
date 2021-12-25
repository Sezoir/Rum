#pragma once

#include <chrono>

namespace Rum::Scene
{
    typedef std::chrono::microseconds TimeStep;

    class RObject
    {
    public:
        virtual void update(const TimeStep& timestep){};
        virtual void draw(){};
        virtual void load(){};
        virtual void unload(){};
    };

} // namespace Rum::Scene