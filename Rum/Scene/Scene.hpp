#pragma once
// Std libs
#include <vector>

// External libs
#include <entt/entt.hpp>

namespace Rum::Scene
{
    class Entity;

    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Entity& createEntity();

    private:
        friend class Entity;

        entt::registry mRegistry;
        std::vector<Entity> mEntities;
    };
} // namespace Rum::Scene
