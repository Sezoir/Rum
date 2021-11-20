#include "Scene.hpp"
#include "Entity.hpp"

namespace Rum::Scene
{
    Entity& Scene::createEntity()
    {
        mEntities.emplace_back(*this, mRegistry.create());
        return mEntities.back();
    }
} // namespace Rum::Scene