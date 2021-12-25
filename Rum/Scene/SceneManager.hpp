#pragma once

#include <vector>
#include <memory>
#include "Scene.hpp"

namespace Rum::Scene
{
    class SceneManager
    {
    public:
        SceneManager() = default;
        ~SceneManager() = default;

        template <typename SceneType, typename... T>
        std::shared_ptr<Scene> makeScene(T... args) const
        {
            mScenes.emplace_back(std::make_shared<SceneType>(args...));
            return mScenes.back();
        }

        // @TODO: setMainScene, setActiveScene, setActiveScenes,
    private:
        std::vector<std::shared_ptr<Scene>> mScenes;
    };
} // namespace Rum::Scene
