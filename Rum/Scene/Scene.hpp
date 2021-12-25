#pragma once
// Std libs
#include <vector>
#include <memory>
// External libs
#include <entt/entt.hpp>
// Project files
#include "RObject.hpp"

namespace Rum::Scene
{
    class Entity;

    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        std::unique_ptr<Entity> createEntity();
        void registerObject(std::shared_ptr<RObject> drawable);

        void onUpdate(const TimeStep& timestep);
        void onDraw();

    private:
        friend class Entity;

        entt::registry mRegistry;
        std::vector<std::shared_ptr<RObject>> mObjects;
    };
} // namespace Rum::Scene
