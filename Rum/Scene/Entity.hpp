#pragma once
// External libs
#include <entt/entt.hpp>
// Project files
#include "Scene.hpp"
#include "Core/Assert.hpp"

namespace Rum::Scene
{
    /**
     * Used to store properties of some object. For example: position; rotation, etc
     * Useful for when you want to iterate through just some shared property of several objects in a `Scene`.
     */
    class Entity
    {
    public:
        Entity(Scene& scene, entt::entity&& entity);
        ~Entity();

        template <typename COMPONENT, typename... COMP_ARGS>
        void addComponent(COMP_ARGS... args)
        {
            RUM_CORE_ASSERT(!hasComponent<COMPONENT>(), "Component already exists in entity.");
            mScene.mRegistry.emplace<COMPONENT>(mEntity, args...);
        }

        template <typename COMPONENT>
        COMPONENT getComponent() const
        {
            RUM_CORE_ASSERT(hasComponent<COMPONENT>(), "Component does not exist in entity.");
            return mScene.mRegistry.get<COMPONENT>(mEntity);
        }

        template <typename COMPONENT>
        bool hasComponent() const
        {
            return mScene.mRegistry.any_of<COMPONENT>(mEntity);
        }

    private:
        Scene& mScene;
        entt::entity mEntity;
    };
} // namespace Rum::Scene
