#include "Entity.hpp"
namespace Rum::Scene
{
    Entity::Entity(Scene& scene, entt::entity&& entity)
        : mScene(scene)
        , mEntity(entity)
    {
    }

    Entity::~Entity()
    {
        mScene.mRegistry.destroy(mEntity);
    }
} // namespace Rum::Scene
